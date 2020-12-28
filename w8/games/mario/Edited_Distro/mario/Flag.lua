Flag = Class{}

function Flag:init(map)
    self.width = 16
    self.height = 16

    self.map = map

    self.x = map.tileWidth * 10
    self.y = map.tileHeight * (map.mapHeight / 2 - 1) - self.height

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