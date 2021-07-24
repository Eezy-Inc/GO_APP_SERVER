require 'socket'

        # starttime = Process.clock_gettime(Process::CLOCK_MONOTONIC)

# local
s = TCPSocket.new 'localhost', 4221
s.write("/home/matt/Documents/GIT/GO_APP/server/tmp/#{ARGV[0]}.c\n")

# remote
# s = TCPSocket.new '85.89.102.14', 4221
# s.write("/home/matt/Documents/GO_APP_SERVER/tmp/#{ARGV[0]}.c\n")

        # s.write("/home/matt/Documents/GO_APP_SERVER/tmp/#{ARGV[0]}.c\n")

s.each_line do |line|
        # puts line
end

s.close
        # endtime = Process.clock_gettime(Process::CLOCK_MONOTONIC)
        # elapsed = endtime - starttime
        # # puts "Elapsed: #{elapsed}"