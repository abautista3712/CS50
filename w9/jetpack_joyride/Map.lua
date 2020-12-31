-- Map quads generated from spritesheet onto level

require 'Util'

require 'Flag'

Map = Class{}

-- Utility Tiles
TILE_EMPTY = -1

-- Star Tiles
SINGLE_STAR = 2
SHOOTING_STAR_LEFT = 14
SHOOTING_STAR_RIGHT = 15
TWINKLE_STAR_1 = 5
TWINKLE_STAR_2 = 6
TWINKLE_STAR_3 = 9

-- Asteroid Tiles
ASTEROID_TOP_LEFT = 3
ASTEROID_TOP_RIGHT = 4
ASTEROID_BOT_LEFT = 7
ASTEROID_BOT_RIGHT = 8

-- Miscellaneous Space Tiles
GALAXY = 10
PLANETS = 11
ALIEN = 12
ROCKET = 13

-- OOB Tile
OOB = 16

local SCROLL_SPEED = 62

-- Constructor for map object
function Map:init()

    self.spritesheet = love.graphics.newImage('graphics/spritesheet.png')
    self.sprites = generateQuads(self.spritesheet, 16, 16)
    -- self.music = love.audio.newSource('sounds/music.wav', 'static')

    self.tileWidth = 16
    self.tileHeight = 16
    self.mapWidth = 100
    self.mapHeight = 28
    self.tiles = {}

    self.gravity = 3

    self.player = Player(self)

    -- Camera offsets
    self.camX = 0
    self.camY = -3

    -- Cache width and height of map in pixels
    self.mapWidthPixels = self.mapWidth * self.tileWidth
    self.mapHeightPixels = self.mapHeight * self.tileHeight

    -- Fill map with empty tiles
    for y = 1, self.mapHeight do
        for x = 1, self.mapWidth do
            
            -- support for multiple sheets per tile; storing tiles as tables 
            self:setTile(x, y, TILE_EMPTY)
        end
    end
    
    -- Generating the terrain using vertical scan lines
    local x = 1
    while x < self.mapWidth do
        -- Generate asteroid belts
        if x % 10 == 0 and x > 10 then
            local asteroidGap = math.random(2, 10)
            for y = 0, self.mapHeight / 2, 2 do
                if y >= asteroidGap and y < asteroidGap + 4 then
                    self:setTile(x, y, TILE_EMPTY)
                else
                    self:setTile(x, y, ASTEROID_TOP_LEFT)
                    self:setTile(x, y + 1, ASTEROID_BOT_LEFT)
                    self:setTile(x + 1, y, ASTEROID_TOP_RIGHT)
                    self:setTile(x + 1, y + 1, ASTEROID_BOT_RIGHT)
                end
            end
            x = x + 2
        else
            -- Generate shooting star 
            if math.random(200) == 1 then
                local spriteStart = math.random(self.mapHeight / 2)
                self:setTile(x, spriteStart, SHOOTING_STAR_LEFT)
                self:setTile(x + 1, spriteStart, SHOOTING_STAR_RIGHT)
                if (x + 1) % 10 ~= 0 then
                    x = x + 2
                end

            -- Generate galaxy
            elseif math.random(200) == 1 then
                local spriteStart = math.random(self.mapHeight / 2)
                self:setTile(x, spriteStart, GALAXY)
                x = x + 1

            -- Generate planets
            elseif math.random(200) == 1 then
                local spriteStart = math.random(self.mapHeight / 2)
                self:setTile(x, spriteStart, PLANETS)
                x = x + 1

            -- Generate alien
            elseif math.random(200) == 1 then
                local spriteStart = math.random(self.mapHeight / 2)
                self:setTile(x, spriteStart, ALIEN)
                x = x + 1

            -- Generate rocket
            elseif math.random(200) == 1 then
                local spriteStart = math.random(self.mapHeight / 2)
                self:setTile(x, spriteStart, ROCKET)
                x = x + 1
                
            -- Generate single star
            elseif math.random(200) == 1 then
                local spriteStart = math.random(self.mapHeight / 2)
                self:setTile(x, spriteStart, SINGLE_STAR)
                x = x + 1
            end


            -- Generate twinkle star 1
            if math.random(25) == 1 then
                local spriteStart = math.random(self.mapHeight / 2)
                self:setTile(x, spriteStart, TWINKLE_STAR_1)

            -- Generate twinkle star 2
            elseif math.random(4) == 1 then
                local spriteStart = math.random(self.mapHeight / 2)
                self:setTile(x, spriteStart, TWINKLE_STAR_2)

            -- Generate twinkle star 3
            elseif math.random(4) == 1 then
                local spriteStart = math.random(self.mapHeight / 2)
                self:setTile(x, spriteStart, TWINKLE_STAR_3)
            else
                x = x + 1
            end
        end
    end

    -- Generate Out of Bounds tiles
        for x = 1, self.mapWidth do
            self:setTile(x, 0, OOB)
        end

        for x = 1, self.mapWidth do
            self:setTile(x, self.mapHeight / 2 + 1, OOB)
        end

    -- start the background music
    -- self.music:setLooping(true)
    -- self.music:play()
end

-- Return whether a given tile is collidable
function Map:collides(tile)
    -- define our collidable tiles
    local collidables = {
        ASTEROID_BOT_LEFT, ASTEROID_BOT_RIGHT, ASTEROID_TOP_LEFT, ASTEROID_TOP_RIGHT
    }

    -- Iterate and return true if our tile type matches
    for _, v in ipairs(collidables) do
        if tile.id == v then
            return true
        end
    end

    return false
end

-- return whether a given tile is end level trigger
function Map:end_trigger(tile)
    -- define our collidable tiles
    local end_trigger = {
        FLAGPOLE_BOT, FLAGPOLE_MID, FLAGPOLE_TOP
    }

    -- iterate and return true if our tile type matches
    for _, v in ipairs(end_trigger) do
        if tile.id == v then
            return true
        end
    end

    return false
end

-- Function to update camera offset with delta time
function Map:update(dt)
    self.player:update(dt)
    -- self.flag:update(dt)
    
    -- Keep camera's X coordinate following the player, preventing camera from
    -- scrolling past 0 to the left and the map's width
    self.camX = math.max(0, math.min(self.player.x - VIRTUAL_WIDTH / 2,
        math.min(self.mapWidthPixels - VIRTUAL_WIDTH, self.player.x)))
end

-- Gets the tile type at a given pixel coordinate
function Map:tileAt(x, y)
    return {
        x = math.floor(x / self.tileWidth) + 1,
        y = math.floor(y / self.tileHeight) + 1,
        id = self:getTile(math.floor(x / self.tileWidth) + 1, math.floor(y / self.tileHeight) + 1)
    }
end

-- Returns an integer value for the tile at a given x-y coordinate
function Map:getTile(x, y)
    return self.tiles[(y - 1) * self.mapWidth + x]
end

-- Sets a tile at a given x-y coordinate to an integer value
function Map:setTile(x, y, id)
    self.tiles[(y - 1) * self.mapWidth + x] = id
end

-- Renders our map to the screen, to be called by main's render
function Map:render()
    for y = 1, self.mapHeight do
        for x = 1, self.mapWidth do
            local tile = self:getTile(x, y)
            if tile ~= TILE_EMPTY then
                love.graphics.draw(self.spritesheet, self.sprites[tile],
                    (x - 1) * self.tileWidth, (y - 1) * self.tileHeight)
            end
        end
    end

    self.player:render()
end
