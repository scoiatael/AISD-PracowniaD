Testfile = 'test.in'
Main = './main'
Test = './test'

def randi(i=100); (rand * i).floor; end
def randp; (randi(2) == 0) ? '.' : 'x'; end

def random_data
  run_number, modulo = [randi + 2, randi(10000000) + 10]
  patterns = (0...randi + 1).map do
    (0...3).map { (0...3).map { randp } .join('') } .join("\n")
  end

  <<-EOF
#{run_number} #{patterns.size} #{modulo}
#{patterns.join("\n")}
  EOF
end

def test(number, string)
  file = File.open(Testfile, 'w')
  file << string
  file.close

  result = []
  [Main, Test].each do |prog|
    out = `zsh -c 'cat #{Testfile} | time #{prog}'`
    result << out.split(' ').last.to_i
  end
  number = result[1] if number == -1
  fail "Wrong, got #{result}, expected #{number}" unless result[0] == number && result[1] == number
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

3.times { test(-1, random_data) }

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
