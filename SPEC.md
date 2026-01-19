## v0 commands

SET key value

GET key

DEL key

INFO


## Output Behavior

GET missing → print (nil)

DEL missing → print 0

DEL existing → print 1

SET → print OK

## Notes

“Single-threaded, in-memory, string→string store (for now).”
