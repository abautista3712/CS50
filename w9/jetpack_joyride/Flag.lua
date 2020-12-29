Flag = Class{}

PYRAMID_END = 25
PYRAMID_HEIGHT = 6

FLAGPOLE_DIST = 7
FLAG_TOP = 1

function Flag:init(map)
    self.width = 16
    self.height = 16

    self.map = map

    self.x = map.tileWidth * (PYRAMID_END + FLAGPOLE_DIST) - (map.tileWidth * 0.5)
    self.y = (map.tileHeight * (FLAG_TOP)) + 5
 
    self.texture = love.graphics.newImage('graphics/spritesheet.png')
    self.frames = generateQuads(self.texture, 16, 16)

    self.state = 'flying'    

    self.animations = {
        ['flying'] = Animation {
            texture = self.texture,
            frames = {
                self.frames[13], self.frames[14], self.frames[15], self.frames[14]
            },
            interval = 0.15
        }
    }

    self.animation = self.animations['flying']
    self.currentFrame = self.animation:getCurrentFrame()
end

function Flag:update(dt)
    self.animation:update(dt)
    self.currentFrame = self.animation:getCurrentFrame()
end

function Flag:render()
    love.graphics.draw(self.texture, self.animation:getCurrentFrame(), self.x, self.y)
end