require 'socket'

# starttime = Process.clock_gettime(Process::CLOCK_MONOTONIC)
s = TCPSocket.new '85.89.102.14', 4221

s.write("/home/matt/Documents/GO_APP_SERVER/tmp/#{ARGV[0]}.c\n")

s.each_line do |line|
        # puts line
end

s.close
# endtime = Process.clock_gettime(Process::CLOCK_MONOTONIC)
# elapsed = endtime - starttime
# # puts "Elapsed: #{elapsed}"