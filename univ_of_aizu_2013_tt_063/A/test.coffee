_ = require "underscore"

f = (n, x)->
  if x <= 0
    0
  else
    ( n - x + 1 ) * ( n - x + 1 ) + f(n, x - 1)

g = (n, x, y)->
  if x <= 0
    g(n, n, y - 1)
  else if y <= 0
    0
  else
    ( n - x + 1 ) * ( n - y + 1 ) + g(n, x - 1, y)

_([1..10]).each (x)->
  console.log "#{x}: f = #{f(x, x)}"
  console.log "#{x}: g = #{g(x, x, x) - f(x, x)}"

