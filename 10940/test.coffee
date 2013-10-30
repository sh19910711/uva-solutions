_ = require "underscore"

f = (x)->
  A = [1..x]
  while A.length >= 2
    A = g A
  A.shift()

g = (A)->
  A.shift()
  A.push A.shift()
  A

ret = _([1..257]).map f

_(ret).each (v, k)->
  console.log "#{k + 1} #{v}"

