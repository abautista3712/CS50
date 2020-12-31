--[[
    Represents our player in the game, with its own sprite.
]]

Player = Class{}

-- local WALKING_SPEED = 140
local BOOST_VELOCITY = 100

function Player:init(map)
    
    self.x = 0
    self.y = 0
    self.width = 16
    self.height = 20

    -- offset from top left to center to support sprite flipping
    self.xOffset = 8
    self.yOffset = 10

    -- reference to map for checking tiles
    self.map = map
    self.texture = love.graphics.newImage('graphics/jetpack_crewmate.png')

    self.music = {
        ['death'] = love.audio.newSource('music/yoitrax-long-way.wav', 'stream'),
        ['victory'] = love.audio.newSource('music/fsm-team-inspirational-audio-logo.wav', 'static')
    }

    -- sound effects
    self.sounds = {
        ['boost'] = love.audio.newSource('sounds/boost.wav', 'static'),
    }

    -- animation frames
    self.frames = {}

    -- current animation frame
    self.currentFrame = nil

    -- used to determine behavior and animations
    self.state = 'flying'

    -- determines sprite flipping
    self.direction = 'right'

    -- x and y velocity
    self.dx = 60 * 2
    self.dy = 0

    -- position on top of map tiles
    self.y = map.tileHeight * ((map.mapHeight - 2) / 4)
    self.x = map.tileWidth * 5

    -- initialize all player animations
    self.animations = {
        ['idle'] = Animation({
            texture = self.texture,
            frames = {
                love.graphics.newQuad(0, 0, 16, 20, self.texture:getDimensions())
            }
        }),
        ['flying'] = Animation({
            texture = self.texture,
            frames = {
                love.graphics.newQuad(0, 0, 16, 20, self.texture:getDimensions()),
                love.graphics.newQuad(16, 0, 16, 20, self.texture:getDimensions()),
                love.graphics.newQuad(32, 0, 16, 20, self.texture:getDimensions()),
                love.graphics.newQuad(16, 0, 16, 20, self.texture:getDimensions()),
            },
            interval = 0.05
        })
    }

    -- initialize animation and current frame we should render
    self.animation = self.animations['idle']
    self.currentFrame = self.animation:getCurrentFrame()

    -- behavior map we can call based on player state
    self.behaviors = {
        ['idle'] = function(dt)
            -- add spacebar functionality to trigger flying state
            if love.keyboard.wasPressed('space') then
                self.dy = -BOOST_VELOCITY
                self.state = 'flying'
                self.animation = self.animations['flying']
                self.sounds['boost']:play()
            else
                self.dy = self.dy + self.map.gravity
            end
        end,
        ['flying'] = function(dt)
            -- handle transition from flying to idle states
            if love.keyboard.isDown('space') then
                self.dy = -BOOST_VELOCITY
                self.animation = self.animations['flying']
                -- self.sounds['jump']:play()
            else
                self.state = 'idle'
                self.animation = self.animations['idle']
            end

            -- check for collisions moving right
            self:checkRightCollision()
            self.dy = self.dy + self.map.gravity
        end,
        ['death'] = function(dt)
            self.dx = 0
            self.dy = 0

            self.music['death']:setLooping(true)
            self.music['death']:play()
        end,
        ['victory'] = function(dt)
            self.dx = 0
            self.dy = 0

            self.music['victory']:setLooping(false)
            self.music['victory']:play()
        end
    }
end

function Player:update(dt)
    self.behaviors[self.state](dt)
    self.animation:update(dt)
    self.currentFrame = self.animation:getCurrentFrame()
    self.x = self.x + self.dx * dt

    -- End Level Conditions
    self:handleEndGame()
    self:calculateUpDownCollision()

    -- apply velocity
    self.y = self.y + self.dy * dt
end

-- Logic for up/down collision
function Player:calculateUpDownCollision()
    
    if self.dy < 0 or self.dy > 0 then
        if self.map:collides(self.map:tileAt(self.x + self.width + 1, self.y)) or
        self.map:collides(self.map:tileAt(self.x + self.width + 1, self.y + self.height)) then

            self.map.music:stop()

            function love.draw()
                push:apply('start')
                love.graphics.setFont(retroFont)
                love.graphics.printf('YOU CRASHED INTO AN ASTEROID', 0, VIRTUAL_HEIGHT / 2 - 20, VIRTUAL_WIDTH, 'center')
                love.graphics.printf('RESTART TO PLAY AGAIN!', 0, VIRTUAL_HEIGHT / 2 - 10, VIRTUAL_WIDTH, 'center')
                push:apply('end')
            end

            self.state = 'death'
        
        end
    end
end

-- Logic for right collision
function Player:checkRightCollision()
    if self.dx > 0 then
        -- check if there's a tile directly beneath us
        if self.map:collides(self.map:tileAt(self.x + self.width, self.y + 1)) or
            self.map:collides(self.map:tileAt(self.x + self.width, self.y + self.height + 1)) then
            
            -- if so, reset velocity and position and change state
            self.dx = 0
            self.dy = 0
        end
    end
end

-- End game logic
function Player:handleEndGame()
    if self.map:tileAt(self.x, self.y).id == OOB or
        self.map:tileAt(self.x + self.width - 1, self.y + self.height - 1).id == OOB then

        self.map.music:stop()

        function love.draw()
            push:apply('start')
            love.graphics.setFont(retroFont)
            love.graphics.printf('YOU GOT SUCKED OUT INTO THE VOID', 0, VIRTUAL_HEIGHT / 2 - 20, VIRTUAL_WIDTH, 'center')
            love.graphics.printf('RESTART TO PLAY AGAIN!', 0, VIRTUAL_HEIGHT / 2 - 10, VIRTUAL_WIDTH, 'center')
            push:apply('end')
        end
        
        self.state = 'death'
    
    elseif self.map:tileAt(self.x, self.y).id == FINISH or
        self.map:tileAt(self.x + self.width - 1, self.y + self.height - 1).id == FINISH then

        self.map.music:stop()

        function love.draw()
            push:apply('start')
            love.graphics.setFont(retroFont)
            love.graphics.printf('CONGRATULATIONS! YOU ESCAPED THE ASTEROID FIELD!', 0, VIRTUAL_HEIGHT / 2 - 20, VIRTUAL_WIDTH, 'center')
            love.graphics.printf('RESTART TO PLAY AGAIN!', 0, VIRTUAL_HEIGHT / 2 - 10, VIRTUAL_WIDTH, 'center')
            push:apply('end')
        end

        self.state = 'victory'

    end
end

function Player:render()
    -- draw sprite with scale factor and offsets
    local scale = 2

    love.graphics.draw(self.texture, self.currentFrame, math.floor(self.x + self.xOffset),
        math.floor(self.y + self.yOffset), 0, scale, scale, self.xOffset, self.yOffset)
end
