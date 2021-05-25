local skynet = require "skynet"
local socket = require "skynet.socket"

local function accept(clientfd, addr)
    skynet.newservice("agent", clientfd, addr)
end

skynet.start(function ()
    local listenfd = socket.listen("0.0.0.0", 55561)
    skynet.uniqueservice("redis")
    skynet.uniqueservice("hall")
    socket.start(listenfd, accept) -- acceptor epoll_ctl
end)

-- 1. 维护连接  网络可达
-- 2. 可以检测  对端是否 死锁 或者 崩溃
