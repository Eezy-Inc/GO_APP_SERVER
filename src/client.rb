require 'socket'

s = TCPSocket.new 'localhost', 4221

s.write("/home/matt/Documents/GIT/DART/Database/server/src/#{ARGV[0]}.c\n")

s.each_line do |line|
        puts line
end

s.close