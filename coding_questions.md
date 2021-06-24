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
13.
14. see question 7
15. virtual function are declared in the base class but can be redefined by the inherited class. in C++ we use virtual dispatch.
16. using vargs list syntax in C, it's an awfull macro.
17. synchronization with barrier logic.

