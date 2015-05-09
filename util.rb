def randi(i=100000)
  (rand * i).to_i
end

def randp
  randi(10**8) - 10**7
end

def newlined(arg)
  "#{arg.to_s}\n"
end

def pos(string)
  x1, y1, x2, y2 = string.split(/\W+/).map(&:to_i)
  [[x1, y1], [x2, y2]]
end

def dist(p1, p2)
  x1, y1 = p1
  x2, y2 = p2
  Math.sqrt((x1-x2)**2 + (y1-y2)**2)
end

def dist_pos(str)
  dist(*pos(str))
end
