-- config.lua

PlayerConfig = {
    speed = 200.0,
    start_x = 100.0,
    start_y = 100.0
}

-- Dodane argumenty: screen_w i screen_h
function update_player(x, y, speed, dt, up, down, left, right, screen_w, screen_h)
    local dx = 0
    local dy = 0

    if up then dy = dy - 1 end
    if down then dy = dy + 1 end
    if left then dx = dx - 1 end
    if right then dx = dx + 1 end

    if dx ~= 0 and dy ~= 0 then
        local length = math.sqrt(dx*dx + dy*dy)
        dx = dx / length
        dy = dy / length
    end

    local new_x = x + (dx * speed * dt)
    local new_y = y + (dy * speed * dt)

    -- Rozmiar gracza (np. 50 pikseli), żeby nie uciekał za ekran prawym i dolnym bokiem
    local player_size = 50 

    -- Kolizje z krawędziami ekranu (zakładamy punkt 0,0 w lewym górnym rogu)
    if new_x < 0 then new_x = 0 end
    if new_y < 0 then new_y = 0 end
    if new_x > screen_w - player_size then new_x = screen_w - player_size end
    if new_y > screen_h - player_size then new_y = screen_h - player_size end

    return new_x, new_y
end
