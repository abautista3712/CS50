--[[
    Contains tile data and necessary code for rendering a tile map to the
    screen.
]]

require 'Util'

require 'Flag'

Map = Class{}

TILE_BRICK = 1

-- utility tiles
TILE_EMPTY = -1

-- star tiles
SINGLE_STAR = 2
SHOOTING_STAR_LEFT = 14
SHOOTING_STAR_RIGHT = 15
TWINKLE_STAR_1 = 5
TWINKLE_STAR_2 = 6
TWINKLE_STAR_3 = 9

-- asteroid tiles
ASTEROID_TOP_LEFT = 3
ASTEROID_TOP_RIGHT = 4
ASTEROID_BOT_LEFT = 7
ASTEROID_BOT_RIGHT = 8

-- miscellaneous space tiles
GALAXY = 10
PLANETS = 11
ALIEN = 12
ROCKET = 13

-- bush tiles
BUSH_LEFT = 2
BUSH_RIGHT = 3

-- mushroom tiles
MUSHROOM_TOP = 10
MUSHROOM_BOTTOM = 11

-- jump block
JUMP_BLOCK = 5
JUMP_BLOCK_HIT = 9

-- flag blocks
FLAGPOLE_BOT = 16
FLAGPOLE_MID = 12
FLAGPOLE_TOP = 8

-- a speed to multiply delta time to scroll map; smooth value
local SCROLL_SPEED = 62

PYRAMID_END = 75
PYRAMID_HEIGHT = 6

FLAGPOLE_DIST = 7

-- constructor for our map object
function Map:init()

    self.spritesheet = love.graphics.newImage('graphics/spritesheet.png')
    self.sprites = generateQuads(self.spritesheet, 16, 16)
    -- self.music = love.audio.newSource('sounds/music.wav', 'static')

    self.tileWidth = 16
    self.tileHeight = 16
    self.mapWidth = 100
    self.mapHeight = 28
    self.tiles = {}

    -- applies positive Y influence on anything affected
    self.gravity = 1

    -- associate player with map
    self.player = Player(self)
    -- self.flag = Flag(self)

    -- camera offsets
    self.camX = 0
    self.camY = -3

    -- cache width and height of map in pixels
    self.mapWidthPixels = self.mapWidth * self.tileWidth
    self.mapHeightPixels = self.mapHeight * self.tileHeight

    -- first, fill map with empty tiles
    for y = 1, self.mapHeight do
        for x = 1, self.mapWidth do
            
            -- support for multiple sheets per tile; storing tiles as tables 
            self:setTile(x, y, TILE_EMPTY)
        end
    end
    
    -- begin generating the terrain using vertical scan lines
    local x = 1
    while x < self.mapWidth do
        -- Generate pyramid
        if x >= PYRAMID_END - PYRAMID_HEIGHT and x <= PYRAMID_END then
            for i = 0, PYRAMID_HEIGHT do   
                for y = self.mapHeight / 2 - i, self.mapHeight do
                    self:setTile(x, y, TILE_BRICK)
                end
                x = x + 1
            end
        -- Prepare end of level with no pitfalls
        -- elseif x > PYRAMID_END then
            -- for y = self.mapHeight / 2, self.mapHeight do
            --     self:setTile(x, y, TILE_BRICK)
            -- end
            
            -- if x == PYRAMID_END + FLAGPOLE_DIST then
            --     self:setTile(x, self.mapHeight / 2 - 12, FLAGPOLE_TOP)

            --     for y = self.mapHeight / 2 - 11, self.mapHeight / 2 - 2 do
            --         self:setTile(x, y, FLAGPOLE_MID)
            --     end

            --     self:setTile(x, self.mapHeight / 2 - 1, FLAGPOLE_BOT)
            -- end

            -- x = x + 1
        else
            -- 1% chance to generate shooting star 
            if math.random(100) == 1 then
                    
                -- choose a random vertical spot in view
                local spriteStart = math.random(self.mapHeight / 2)

                self:setTile(x, spriteStart, SHOOTING_STAR_LEFT)
                self:setTile(x + 1, spriteStart, SHOOTING_STAR_RIGHT)

                x = x + 2

            -- 1% chance to generate galaxy
            elseif math.random(250) == 1 then
                                    
                -- choose a random vertical spot in view
                local spriteStart = math.random(self.mapHeight / 2)

                self:setTile(x, spriteStart, GALAXY)

                x = x + 1

            -- 1% chance to generate planets
            elseif math.random(250) == 1 then
                                    
                -- choose a random vertical spot in view
                local spriteStart = math.random(self.mapHeight / 2)

                self:setTile(x, spriteStart, PLANETS)

                x = x + 1

            -- 1% chance to generate alien
            elseif math.random(250) == 1 then
                                    
                -- choose a random vertical spot in view
                local spriteStart = math.random(self.mapHeight / 2)

                self:setTile(x, spriteStart, ALIEN)

                x = x + 1

            -- 1% chance to generate rocket
            elseif math.random(250) == 1 then
                                    
                -- choose a random vertical spot in view
                local spriteStart = math.random(self.mapHeight / 2)

                self:setTile(x, spriteStart, ROCKET)

                x = x + 1

                
                -- 5% chance to generate single star
            elseif math.random(200) == 1 then
                    
                -- choose a random vertical spot in view
                local spriteStart = math.random(self.mapHeight / 2)
                    
                self:setTile(x, spriteStart, SINGLE_STAR)
                    
                x = x + 1
                    
            end

            -- 5% chance to generate twinkle star 1
            if math.random(25) == 1 then
                    
                -- choose a random vertical spot in view
                local spriteStart = math.random(self.mapHeight / 2)

                self:setTile(x, spriteStart, TWINKLE_STAR_1)

                -- x = x + 1

            -- 10% chance to generate twinkle star 2
            elseif math.random(7) == 1 then
                    
                -- choose a random vertical spot in view
                local spriteStart = math.random(self.mapHeight / 2)

                self:setTile(x, spriteStart, TWINKLE_STAR_2)

                -- x = x + 1

            -- 10% chance to generate twinkle star 3
            elseif math.random(7) == 1 then
                    
                -- choose a random vertical spot in view
                local spriteStart = math.random(self.mapHeight / 2)

                self:setTile(x, spriteStart, TWINKLE_STAR_3)

                -- x = x + 1
                
            else

                x = x + 1

            end
            -- 5% chance to generate a mushroom
            -- if math.random(20) == 1 then
            --     -- left side of pipe
            --     self:setTile(x, self.mapHeight / 2 - 2, MUSHROOM_TOP)
            --     self:setTile(x, self.mapHeight / 2 - 1, MUSHROOM_BOTTOM)

            --     -- creates column of tiles going to bottom of map
            --     for y = self.mapHeight / 2, self.mapHeight do
            --         self:setTile(x, y, TILE_BRICK)
            --     end

            -- else
            --     -- next vertical scan line
            --     x = x + 1
            -- end

            -- -- 10% chance to generate bush, being sure to generate away from edge
            -- elseif math.random(10) == 1 and x < self.mapWidth - 3 then
            --     local bushLevel = self.mapHeight / 2 - 1

            --     -- place bush component and then column of bricks
            --     self:setTile(x, bushLevel, BUSH_LEFT)
            --     for y = self.mapHeight / 2, self.mapHeight do
            --         self:setTile(x, y, TILE_BRICK)
            --     end
            --     x = x + 1
            --     self:setTile(x, bushLevel, BUSH_RIGHT)
            --     for y = self.mapHeight / 2, self.mapHeight do
            --         self:setTile(x, y, TILE_BRICK)
            --     end
            --     x = x + 1
                
            -- -- 10% chance to not generate anything, creating a gap
            -- elseif math.random(10) ~= 1 then
                
            --     -- creates column of tiles going to bottom of map
            --     for y = self.mapHeight / 2, self.mapHeight do
            --         self:setTile(x, y, TILE_BRICK)
            --     end

            --     -- chance to create a block for Mario to hit
            --     if math.random(15) == 1 then
            --         self:setTile(x, self.mapHeight / 2 - 4, JUMP_BLOCK)
            --     end

            --     -- next vertical scan line
            --     x = x + 1

            -- else
            --     -- increment X so we skip two scanlines, creating a 2-tile gap
            --     x = x + 2
        end
    end

    -- start the background music
    -- self.music:setLooping(true)
    -- self.music:play()
end

-- return whether a given tile is collidable
function Map:collides(tile)
    -- define our collidable tiles
    local collidables = {
        TILE_BRICK, JUMP_BLOCK, JUMP_BLOCK_HIT,
        MUSHROOM_TOP, MUSHROOM_BOTTOM
    }

    -- iterate and return true if our tile type matches
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

-- function to update camera offset with delta time
function Map:update(dt)
    self.player:update(dt)
    -- self.flag:update(dt)
    
    -- keep camera's X coordinate following the player, preventing camera from
    -- scrolling past 0 to the left and the map's width
    self.camX = math.max(0, math.min(self.player.x - VIRTUAL_WIDTH / 2,
        math.min(self.mapWidthPixels - VIRTUAL_WIDTH, self.player.x)))
end

-- gets the tile type at a given pixel coordinate
function Map:tileAt(x, y)
    return {
        x = math.floor(x / self.tileWidth) + 1,
        y = math.floor(y / self.tileHeight) + 1,
        id = self:getTile(math.floor(x / self.tileWidth) + 1, math.floor(y / self.tileHeight) + 1)
    }
end

-- returns an integer value for the tile at a given x-y coordinate
function Map:getTile(x, y)
    return self.tiles[(y - 1) * self.mapWidth + x]
end

-- sets a tile at a given x-y coordinate to an integer value
function Map:setTile(x, y, id)
    self.tiles[(y - 1) * self.mapWidth + x] = id
end

-- renders our map to the screen, to be called by main's render
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
    -- self.flag:render()
end
