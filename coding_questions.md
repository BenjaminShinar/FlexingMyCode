# Coding Questions answers
a short description of how I think this should be answered. I will use C language concepts for most of them.
1. sort Jar array with colored balls(red,yellow,green). 
- keep pointers to first yellow(default=0) and last yellow (default=end) and the running pointer.
- iterate over the array, if red, swap with first yellow, and advance the first yellow pointer. if green, replace with last yellow, and decrease the pointer back.
- eventually the running pointer will reach the 'last yellow'. this means that there are no more unsorted balls.
- alternativly = use a sorting count.
2. reverse a linked list.
3. the sensor doesn't know now the direction of the movement.
- if we have two sensors and we decide the direction based on timing, we can still run into problems.
- if we can identify people with the sensor, we can keep a dictionary. add if doesn't exists, remove if it does. the number of elements in the dictionary is amount of people in the room. this requires one sensor.
4. determine task state
- check if inside 'life time': after creation and before end. this will return [before creation,after creation]
- compute the combined time of running + pending cylce. then do (now - creation) %(combined). this will return our position in the current cycle. compare this to 'runtime', if below, running, else pending.
5. add counter of objects.
- make a static class member that incrases at creation and decrases at destruction. make it atomic.
6. static keyword in C and C++
- static function in C: limited to translation unit. not linked.
- static function in C++: belongs to the class, can be run without an object.
- static inside function (c, cpp) - a variable inside the function that is stored in the DATA section and keeps its' value across muliple calls to the function.
7. randomly sort an array.
- iterate over the array once.
- for each element, get a random position and swap the current element with that one. should be random enough.
    - I think there is a resource somewhere that discusses the randomness of this.
8. abstract class -  declare a pure virtual function with = 0; other langagues have builtin support.
9. switches - probably has something to with prime numbers:
- switch 1 is on.
- any prime switch is off (pressed ON at 1, and off by the Nth person)
- any number with even number of factors is off.
- I think that any even power of a prime is on. (2^2 = 4{1,2,4}, 2^4=16{1,2,4,8,16}, 2^6=64{1,2,4,16,32,64} 3^2=9{1,3,9}, 3^4=81{1,3,9,81},)
- not sure how to reason about other numbers
- simply write the damn loop (O(N)) and xor it.
10. what does this mean?
11. I dont think this matters. need to write the formula. N=[0..10]
- chance = 0.5* (N/10) + 0.5 *((10-N)/10) should be 0.5 for all values.
12. there is some formula to create the 1st ball jumps, and from there climb by one.
13. **THIS**
14. see question 7
15. virtual function are declared in the base class but can be redefined by the inherited class. in C++ we use virtual dispatch.
16. using vargs list syntax in C, it's an awfull macro.
17. synchronization with barrier logic.
18. print all possible permutations
19. re-implement *strcspn*
20. dictionary can be a trie-tree data strucutre.
* finding permutations recursivly.
* for each iteration, swap the first with the Nth character and check if there exists a route.
* if there is a route, go down the route and repeat for the substring.
* swap back at exit.
* the level finishes when we swapped each position. (N times)
21. **I don't know this**
22. properly serialize a tree?
23. an abstract class can't exists on it's own and can only be instacesized by a subclass.
24. regular virtual function can be overriden by a subclass. pure virtual functions must be overriden.
25. a copy constructer determines how a new object is created from an existing one. you should define one if you want to properly pass/return an object of this class from a function.
* very important when the class contains pointers
* *alternativly, use =default to skip this issue* 
26. the virtual table determines how each object access the virtual functions, this is the overhead of using inheritance and virtual functions. it's another derefence call that we need in runtime.
27. a singletone is a design pattern for keeping only one object of a class in the program, without duplications.
* we use it for objects that control a resource (e.g: logger) or are expensive to create and destroy.
* either a double check lock singleton (check if exits, if not, lock, check again. create.) or inner static member (depending on language).
28. mutex can only be used by the holder, and has only two states (free and locked). semaphore can be used by any thread (you don't have to take a lock before posting to it) and can range from 0 (cant pass through) to N (allow N threas to take).
29. threads of the same process can communicate with synchronization objects, or by changing shared values(global, heap objects, etc... this might be unsafe). processes communicate with signals.
30. implement C *strncmp*
31. implement C *Queue*
32. **parking lot** - feels like we need semaphore?
33. mutex can only be released by the owner, a binary semaphore can be released (post) by any thread.
34. processes have thier own virutal memory stack.threads (of the same process) share the memory stack of the parent process.
35. *see implementation*
* must be O(N) complecity.
* slower version - iterate over all elements with [] syntax.
* faster version - use pointer arithmetics for slight gain in speed. (++ptr).
* tried using threads (split the work across two threads), but it made things slower.
36. **is this a gemoetry problem?**
37. **this is defnitaly a geometry problem**
* **THINK ABOUT THIS**
38. the file size will increase if we globablly initilize it. acessing it might also be slower becuase of cache misses. however, if this function is used manytimes, the cost of initilization might be more of a problem than the acesses and make the program slower.
39. this is 7 all over again. how to randomly sort an array.
40. find max path:
* brute force option - use recursion for each step and then get the best value. this has too high complexity (probably O(N!) or something)
* dynamic programming option. space complexity (N), create a representation of each square in the matrix and store the best path. start from the end, and work backwards.
* maybe we can actually do this in place.
    * start from the end, and work backwards (in a diagonal way), add to each square the 'best sum possible' from that location. so \[N-1\]\[N-1\] is the last square, so add zero to it. \[N-2\]\[N-1\] and \[N-1\]\[N-2\] can only move on way, so add the \[N-1\]\[N-1\] value to them. \[N-2\]\[N-1\] \[N-1\]\[N-2\] both have one possible option, so do the same with them. \[N-2\]\[N-2\] has two possible paths, so add the larger value form both options
    * after going through all options, the best path is 'choose the max of the two options'.
41. **I DON'T KNOW THIS** - probably xors or somethings
42. **this looks like a chain question.** 
* maybe this is a tree strucutre thing? or something tree-like?
* we have a list of matches (a \< b), and we need to use transitivy to implement toatl order.
* the complete list of matches is N * N in size.
* lets say that for each element, we keep all the elments we know the relation with it.
* maybe we can loop recuresivly and fill the list of matches.
* but i think there is a way to do this a tree.
43. implement *FIXED SPACE MEMORYALLOCATION*
44. there is an init() function that identifies the user defined main(argcs, argsv[], env[]) and does some other stuff (globals?)
45. sizeof data types, avoid using regeister specific operations, **more**
46. reimplemnt *memcopy*.
* make sure to align on block size and then copy 8 bytes each time we use = rather than one.
* the source and the destination range might overlap, so it might be better to start from the ending of the rane.
47. context switch is the act of suspending a process (freezing it in place), keeping the Instruction pointer (and maybe others) in the process block and then start running a different process.
* can't happen in the middle of assmbly 'line' - this is an atomic operation.
* likely to happen when meeting an synchronization object, or when the program explicitly calls *yields* to return control to the OS.
48. accessing a globabl variable.
* use an atomic aceeses to the a variable.
* if the a isn't changed, then there's no problem.
49. the memory address of buff is defined on the stack, so it will be reused and the value will be lost.
50. the process control block keeps the location of the instruction pointer.
51. splicing a node from a singly linked list
* O(N) iterate all over the list until ->next is the node to be removed, assing ->next to ->next->next and free the requested node.
* O(1) - swap contents of this node with the next one (requires that data in nodes are stored seperatly), then take next->next and remove ->next, assign -> next to what we took.
52. find loops in linked list
* slow pointer and fast pointer, run until fast reaches 'NULL' or they meet.
* this is O(N) if it's not looped - than fast will reach NULL is n/2.
* if there is a loop, at N step the slow should be inside the loop (worst case),and the fast should reach him in a step or two.
53. allocate and free memory of different sizes
* probably about different algoriths of memory allocation - first fit, best fit, etc..
* we did this with stealing the few bytes before tha memory address to hold the size of the data.
54. **Timers and Callbacks**
* probably requires a global list.
* who dellocates them?
55. not properly using double pointers
* will print 42.
56. ptr was moved and isn't pointing to the start of the allocated data.
57. a is a local varible, it's stored in the thread local stack, it's not shared between threads. no problem.
58. combinatorics: 15 (pairs of same colors) / 30c2 (pairs)
* 30!/(2!(30-2)!) = 30 * 29 / 2    =15*29 = 435.
59. **maximum stack usage?**
60. *elevator algorithm*
* simple elevator - only goes to the requested level, doesn't do stops. imagine an elevator with a dial and not buttons (only one level possible)
* proper elevator, keeps direction. can accept input at all times. at each level, we check the inputs (floors),if current is on - open doors and remove this floor from requested list. if none -stop. if there are stll floors at the requested direction, go in that direction, otherwise, switch direction.
* we might want an elevator with a smarter algortihm.
61. possible, but i don't remember what happens.
62. it's like passing by pointer, we don't create a new object, and we can modify the original, but we use normal syntax and we can't reassign the pointer.
63. diamond inheritance problem - each base class has it's own superbase class, so D has two elements of A, accessed by B.A, C.A. this is why we need virtual inheritance.
64. matrix transpose for N x N
* brute force? for 0..n swap \[n\]\[k\] with a\[k\]\[n\]. maybe.
65. I want to use the xor, but not sure if this is right.
* maybe use deque? each request is recorded in the deque when it's arriving with the sent time, and removed when the ack arrives. when an ack arrives we can compere the times to raise an error, or do a self initiated check on the first elemnt each second to see that there are no old missing elemnts.
* I choose a deque because we want FIFO - a message sent is attacched at the back, but when an ack arrives we start checking from the front, this should work best if the messages are somewhat ordered.
66. A is high priority but is waiting on B (med priority) beacuase C can't run before B. 
* theres probably a name for this, maybe priority passing/sharing?
67. find 3rd on bit.
* brute force - keep counter and shift until we find the 3rd on bit - max 32 shifts.
* keep a lut of the number of On bits for each char.
* keep a lut of the first on bit for each char.
* seperate the int into chars, and find which byte has the nth bit
* if the request byte has just one bit on, use the table to find it, and add the number of bytes*bit to the final answer.
* if the request byte has more than one bit on, either brute force (max 8 shifts), or mask the two half of the byte and use the same method.
* the msking method seems like the better option, actually.
68. find maximum density in time point, feels like a dynamic programming problem.
* this is basically 'find max contigues array'. a list of 1 and 0 where we want to find the longest sequence of 1s.
* we don't need to remember which task is which, we only care about amounts.
* keep 'best start','best amount', 'current start', current amount', 'current position'. if current position is 1, add to current amount, if 0 or end, compare to best amount, switch whatever, and seet the current start to next.
69. **I don't know this**
70. *some weird function*
* the static array should be default initilized to 0s', because it's static.
* we first do something with the first array, it feels like a right shift, and we add x to the first position.
* then we do sumproduct with the extren array.
* we return the sumprocduct of x*a[0] and[0..19999]*a[1...20000]
* we can keep the number this function was called as a static varible, and then we can exit it early.
* **NO IDEA**
71. locked letter
* A writes message, adds Lock A, sends to B.
* B cant read message, but adds Lock B, sends to A.
* A removes Lock A, sends to b
* B removes Lock B, can read message
72. base speed * base travel time + high speed * high speed return time = expected speed * (base travel time + hig speed return tiem).
* (40 *t1) + (x * t1/(x/40)) =80 *(t1 + t1(x/40))
* **Maths, I guess**
73. swap without temp
* use + or xor (not for zero, i think)
74. feels like we saw this earlier, feels like a tree.
75. prisoners lamp?
* can they see the lamp?
    * each time a prisoner is out, if it's his first trip, he the lamp once + the number of times he saw the lamp being flipped. so the first person is 1, the 2nd is 2, if the first is out again, he won't flick the lamp, eventually the last prisoner will flip the light N times (number of prisoners) and they know it's all done.
76. array of size N-2, containg numbers [m...N] except two numbers. find missing numbers in two iterations over the array, withot using new memory. the numbers are min or max.
* xor all the numbers from [M...N] (not the array), get a value.
* iteration 1 on the array, Xor each element with the value, we will get a^b as the final value.
* ???
77. all 4 bools must be the same value. cant remember which we pressed and which were not in each round.
* ????
78. sudoko algorithm
79. parenthesis matching algorithm
* use a stack,
* determine open/close brackets.
* iterate over the expression, any open brackets is added to the stack, a closing brackets compaers against top of stack and if they match, remove, otherwise, error.
* if there are elements in the stack at the end of the expression, error.
* adding a fourth type of patntheses, with no difference between openning and closing.
* 
80. **I don't know geomerty**
81. requires space of 256 bytes.
82. calculate paths. jumping spiderman,
* for each level, the number of paths 
83. divison by five autumaton with binary represtation.
    * 5 = 101
    * 10 = 1010 
    * 15 = 1111
    * 20 = 10100
    * 25 = 11001
84. detect loop in linked list.
85. take the largest?
86. if it has one on bit, it's a power of 2 (2^0 = 1, so this stiil works.)
87. if it's not known at compile time, then virtual dispatch through the virtual table.
88. mirror bits.
89. find shared area between lines
90. ctor can't be virtual because the ctor creates the vtable. dtor can be virtual because we want it to be called from the base class pointer/representation to destroy the sub class data.
91. pass an allocator into the new, use use preallocted data and manage it yourself.
92. build the virtual table manually, have the ctor store function refences in a baseclass container and have the public/protected functions call lookup that table and use the function from it. pimpl idiom.
93. find min/max of an array with 1.5N comparisons:
* if we simply iterate, we can get 2N copmarisons, (all elements are between min and max)
* i have an asnwer for this somewhere..
94. *no idea*
95. *?*
96. again fsm?
97. *I don't do regiesters*
98. *I don't do regiesters or HW*
99. no. data race.
* added atomicity. something about L1 cahces, I guess.
100. no. static class function arent called by an object, they are resolved in compile/link time.
101. **more geomerty**
* i guess we need a perimeter?
102. **???**
103. first person adds a random number and then his salary, next person adds his salary to the number, when the loop ends, the fisrt person removes the random number, now we have the sum of all salaries and no one knows the salary of anybody else.
104. detect active bits, not with loop, not with constatnt table.
* see files?
105. easier version of 76. xor both the array and the numbers, the reminder will be the double number.
106. muiltiply by seven without using + or /?
* maybe bitwise operations?
107. **more geometry**
108. **?**
109. added 1 without using +
* find first off bit (starting from lowers), turn it off, all 1 left to it are now 0.
110. max subarray - dynamic programming, bursa game.
111. Binary search inside shift data.
112. XOR with NAN. **I DONT DO LOGICAL GATES**
113. runner A. he wins by a margin of 0.25 meters. he runs 105 meters faster than what runner B runs 100 meter.
114. **?**
115. xor wont work here
116. look at the youtube video,probably start with 1, and then make sure that each turn you either finish with 1 or 3, 
117. is there a good way to find this?
118. for stack - sizeof()/sizeof(). i don't know about heap allocation, pointer decay. 
119. delete uninitilazed pointer, segfault? or maybe it's the same as delete null. mixing new[] and delete. you shoud use delete[].theres probably an issue with slicing?
120. RTTI - runtime type infernce - how we do inheritance in cpp, virtual table?
121. **more geometry**
122. **I DONT DO LOGICAL GATES**
123. **I DONT DO LOGICAL GATES**
124. measuring time with candles - 45 minutes
burn from both sides to measure half time.
125. flipping bits?




125.









