local map = {}

local const = {}
local const_tmp = {}
local const_metatable = {
    __newindex = function(t, k, v)
        if not t[k] then
            const_tmp[k] = v
        else
            print("do not attemp assign a value to a const variable!")
        end
    end,
    __index = const_tmp
}
setmetatable(const, const_metatable)

function math.randomx(m, n, cnt)
    if cnt > n - m + 1 then
        return {}
    end

    math.randomseed(os.time())

    local t = {}
    local tmp = {}
    while cnt > 0 do
        local x = math.random(m, n)
        if not tmp[x] then
            t[#t + 1] = x
            tmp[x] = 1
            cnt = cnt - 1
        end
    end

    return t
end

function map.init(x_len, y_len)
    const.map_value_background = 0
    const.map_value_user_a = 1
    const.map_value_user_b = 2
    const.map_value_user_c = 3

    map.x_len = x_len
    map.y_len = y_len
    for i = 0, map.x_len - 1 do
        map[i] = {}
        for j = 0, map.y_len - 1 do
            map[i][j] = const.map_value_background
        end
    end

    local random_table_x = math.randomx(0, map.x_len - 1, 3)
    -- local random_table_y = math.randomx(0, map.y_len - 1, 3)

    map.user_a_location = {}
    map.user_a_location.x = random_table_x[1]
    map.user_a_location.y = math.random(0, map.y_len - 1)
    map.user_a_location.value = const.map_value_background

    map.user_b_location = {}
    map.user_b_location.x = random_table_x[2]
    map.user_b_location.y = math.random(0, map.y_len - 1)
    map.user_b_location.value = const.map_value_background

    map.user_c_location = {}
    map.user_c_location.x = random_table_x[3]
    map.user_c_location.y = math.random(0, map.y_len - 1)
    map.user_c_location.value = const.map_value_background

    map.user_location_set(map.user_a_location, {x = map.user_a_location.x, y = map.user_a_location.y})
    map.user_location_set(map.user_b_location, {x = map.user_b_location.x, y = map.user_b_location.y})
    map.user_location_set(map.user_c_location, {x = map.user_c_location.x, y = map.user_c_location.y})
end

function map.user_location_set(user, new_location)
    map[user.x][user.y] = user.value

    user.x = new_location.x
    user.y = new_location.y

    -- map refresh
    local map_value_user = const.map_value_background
    if user == map.user_a_location then
        map_value_user = const.map_value_user_a
    elseif user == map.user_b_location then
        map_value_user = const.map_value_user_b
    elseif user == map.user_c_location then
        map_value_user = const.map_value_user_c
    end

    user.value = map[user.x][user.y] -- backup

    map[user.x][user.y] = map_value_user
end

function map.user_move(user, cmd)
    -- condition handle
    local vx = 0
    local vy = 0
    if cmd == "user_up" then
        vy = -1
    elseif cmd == "user_down" then
        vy = 1
    elseif cmd == "user_left" then
        vx = -1
    elseif cmd == "user_right" then
        vx = 1
    end

    if user.x + vx >= 0 and user.x + vx <= map.x_len - 1 and user.y + vy >= 0 and user.y + vy <= map.y_len - 1 then
        local value = map[user.x + vx][user.y + vy]
        if value == const.map_value_background then
            local new_location = {x = user.x + vx, y = user.y + vy}
            map.user_location_set(user, new_location)
        end
    end
end

function map.show()
    for j = 0, map.y_len - 1 do
        local tmp_str = ""
        for i = 0, map.x_len - 1 do
            tmp_str = tmp_str .. map[i][j]
        end
        print(tmp_str)
    end

    print("user a location: (" .. map.user_a_location.x .. ", " .. map.user_a_location.y .. ")")
    print("user b location: (" .. map.user_b_location.x .. ", " .. map.user_b_location.y .. ")")
    print("user c location: (" .. map.user_c_location.x .. ", " .. map.user_c_location.y .. ")")
end

return map

-- map.init(3, 3)
-- map.show()
-- map.user_move(map.user_a_location, "user_up")
-- map.show()
-- map.user_move(map.user_b_location, "user_left")
-- map.show()
-- map.user_move(map.user_b_location, "user_left")
-- map.show()
-- map.user_move(map.user_b_location, "user_left")
-- map.show()
