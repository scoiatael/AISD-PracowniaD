Testfile = 'test.in'
Main = './main'


def test(number, string)
  file = File.open(Testfile, 'w')
  file << string
  file.close

  out = `zsh -c 'cat #{Testfile} | time #{Main}'`
  result = out.split(' ').last.to_i
  fail "Wrong, got #{result}, expected #{number}" unless result == number
end

test 32592, <<-EOF
3 1 1000000
...
...
...
EOF

test 969696, <<-EOF
5 1 1000000
.xx
x..
.xx
EOF

test 904576, <<-EOF
10 2 1000000
xxx
x..
.xx
..x
.x.
x..
EOF

###
# Test = './test'
# 10.times do
#   file = File.open(Testfile, 'w')

#   size = randi

#   file << newlined(size)

#   size.times { file << newlined("#{randp} #{randp}") }

#   file.close

#   out1 = `zsh -c 'cat #{Testfile} | time #{Main}'`
#   out2 = `zsh -c 'cat #{Testfile} | time #{Test}'`

#   puts out1, out2
#   fail 'Wrong!!1' unless dist_pos(out1) <= dist_pos(out2)
# end
