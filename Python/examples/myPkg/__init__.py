print("initialize myPkg in __init__.py")

# If __all__ is defined, when using "from myPkg import *", only names listed in __all__ is imported 
# That's to say, v and m2 are not imported
__all__ = ["p1"]

# If __all__ is not defined, when using "from myPkg import *", v and m2 is imported
v = 3

#import sys
#print(sys.path)
#print(__name__)

# equals to "from .p2 import m2"
#import myPkg.p2.m2
from .p2 import m2
