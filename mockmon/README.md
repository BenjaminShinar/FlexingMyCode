# MOCKMON

A small project that I can be motivated to work on. A simple version of a battling game. The user (player) will control mock-monsters (mockmons) and battle the computer in a manner similar to the famoues game. 

## Points of intrest
I want to replicate the bugs. over the years, the player community discovered many bugs and glitches in the game, and i wish to see how these might have come into existence. so in some cases I will delibratly have behavior which seems non-sensical. I believe these this bugs were not put in the game intenionally, but were products of software design which was streched beyond what it was intended for, either by the constraints of the availble programming languages or by last minute changes that had to be implemented. therefore, i will try to design this program in a way that those bugs appear organically.
topics which require modifications to create those behaviors are marked as **Gen 1 Shannignas**.


## Tasks and Stages - this will eventuall be the Issues tab

- [ ] Basic program structure
- [x] Player choice modules - allow the user to choose an action
- [x] Create the minimal mockmon class (entity)
- [x] The most simple battle possible - the user has a mockmon and needs to choose the correct option to win
- [x] Design minimal enntities for moves (attacks) and mockmon stats
- [ ] Document code using doxygen standatds(/** /*! ///),
- [ ] create a 'trainer' entity.
- [ ] clean compiler warning with flags and attributes
- [ ] can we use constexpr (constant expressions)?
- [ ] ... TBC

### UniqueId
a uniqueId for all sorts of stuff
- [ ] find a library to use it

### What's a mockmon, actually?
- [ ] basic mockmon class
- [x] stats
- [x] type(s)
- [x] moveset
- [ ] status
- [x] progression (exp)
- [x] uniqeness of stats (iv, ev)
- [ ] mockmon uniquness (name, unique id)
- [ ] mockmon evolution

#### Level Up
- [x] stats increase
- [x] moves are learned
- [ ] evolutions

#### evolution
when a mockmon evolves, what happens?
- [x] evolution lines
- [ ] canceling / rejecting evolutions
- [x] changing stats?
- [ ] learnning new moves?
- [ ] before or after stats change?
- [ ] what happens when more than one evolution is possible

##### different methods of evolution:
- [x] by level up
- [ ] by trade
- [ ] by item

### Mockmon battle mock

#### basics
- [x] a battle with a win / lose conditions
- [x] user can choose actions vs opponent
- [ ] moves that do something and moves that fail
- [x] opponent can do something against user
- [x] moves effect mockmon stats rather than directly the outcome
- [x] damage ranges [0.85-1.0]
- [ ] fix damage ranges so we aligned with smogon calculator
- [ ] moves that block/protect against other moves
- [ ] moves that are dependent on status/condition
- [ ] unique moves (mimic, metronome, mirror move, counter)
- [ ] mockmon stats effect the battle outcome
- [x] critical hits
- [x] moves can hit or miss
- [ ] crash damage moves - user takes damage if they fail!
- [ ] moves can cause status effect
- [ ] moves are effected by stats (accuracy, power)
- [ ] status effects (poison, sleep, confision, etc...)
- [x] the type system! super, normal and not very effective!
- [ ] ... TBC battles are between trainers

#### moves
##### One hit Ko moves
moves that KO the enemy if they hit
Fissure, Guillotine, Horn Drill
- [x] always KO enemy
- [ ] consider type immunties/ resistances?
- [x] always fail when speed (level?) is lower
- [ ] X accuracy effects
- [ ] what happens when using dig?
- [ ] interactions with substitute

##### Status Effects - stats modifers
- [x] moves that change stat modifers
- [ ] conditions modifiers
- [ ] none-glitchy badge boost.
- [ ] **Gen 1 Shannignas** for badge boosts

##### self sacrficing moves
explosion, self destruct
- [ ] ko user
- [ ] half defence

##### Two turns moves
- [x] moves with charging before hitting - dig, fly, skull bash,sky attack,solar beam,
- [ ] moves with invurnability stage - dig, fly
- [x] moves with re-charging after hitting - hyperBeam
- [ ] power points consumption - when damage is done
- [ ] interacton with status effects - paused? stopped? what if i hit myself in confusion is pparalyzed
- [ ] weird **Gen 1 Shannignas**

###### Dig / Fly
- [x] - two turn moves
- [ ] - invernuble stage
- [ ] - interaction with status
- [ ] - PP consumption

###### HyperBean
- [x] - two turn move
- [x] - recharge turn
- [ ] - interaction with status moves
- [ ] - **Gen 1 Shannignas**
- [ ] - PP consumption
- [ ] - PP overflow?

##### Multi turns moves
- [ ] multi turn moves

###### binding moves
Bind, Clamp, Firespin, Wrap.

###### moves that eventually confuse the user
Petal Dance, Thrash

##### Unique moves
moves that require extra carefull consideration
- [ ] leech side
- [ ] counter
- [ ] substitute
- [ ] metronome
- [ ] rage
- [ ] TBC

#### conditions
figure out the voltaile/non volatile split
- [x] inflict condition
- [x] remove condition
- [x] conditions can't be inflicted based on typing
- [x] conditions go away after x turns...
- [x] conditions go away after haze or some other move
- [ ] voltaile contions - bind, flinch, recharging?, semi invurnable?
- [ ] **Gen 1 Shannignas** synergy of toxic, burn, leech seed with each other.
- [ ] which conditions work with each other and which are cancelled?
- [ ] which conditions work with moves special effects (dig, charging/recharging)?
- [ ] pulsing conditions - conditions that do something each turn (poison,burn, etc...)
- [ ] non-pulsing conditions - conditions that just stick to the mockmon with 'active' effects (light screen, reflect, focus energy)

##### flinch - pulse
- [x] mockmon won't move
- [ ] only relevent when going first, think about this

##### burn - pulse
- [x] inflict damage
- [x] doesn't effect fire types
- [x] halfs phyiscal moves attacks
- [ ] more **Gen 1 Shannignas**

##### frozen - pulse
- [x] can't move
- [x] doesn't effect ice types
- [x] thawed by fire attacks (and other attacks?)
- [ ] **Gen 1 Shannignas** Power points glitch
- [ ] thawing with a stored move?

##### paralyzed - pulse
- [x] a chance to not move
- [x] speed reduction
- [x] can be caused by different types of attacks, and mockmon of the same type aren't effected by it.
- [ ] more **Gen 1 Shannignas**

##### poison - pulse
- [x] inflict damage
- [x] doesn't effect poison types, and maybe steel types.
- [ ] effects in the outer world

###### badly poison (toxic)  - pulse
- [ ] badly poison increases the damgage it inflicts each turn.

##### sleep - pulse
- [x] won't move
- [x] chance to wake up
- [x] maximum sleeping turns
- [ ] effected by dream eater
- [ ] when caused by sleep, always 2 turns of sleep

##### confused  - pulse
- [x] chance to hitself 
- [ ] hit self with has no stab and no critical hit, and no random damage ranges
- [x] chance to snap out of confusion
- [ ] how it works with multiturn abilities
- [ ] **Gen 1 Shannignas** glitch where defence is effected by the enemy having reflect (mentioned in the wiki under confusion, not under general glitchs)

##### haze
- [x] remove conditions
- [ ] some conditions shouldnt be removed: non volatile (sleep, burn, poison, paralyze,freeze)
- [x] resets status modifiers
- [ ] reset badge boost
- [ ] **Gen 1 Shannignas**

##### leech seed
figure this one out

##### subsitute
figure this one out as well

##### reflect, light screen - non-pulse
- [x] refelct - change physical defence
- [x] light screen - change only special when defending

##### focus energy - non-pulse
- [x] effect critical hit rate
- [x] **Gen 1 Shannignas**

### Mockmon trainer - the best there ever was like no one was before
anything that should relate to the trainer
- [ ] "no trainer" trainer for wild mockmon
- [ ] move the *A.I* behavior to the trainer class
- [ ] badges?
- [ ] obdience based on badges?
- [ ] items?
- [ ] switching out mockmon?
- [ ] defer stuff from battle? arena?
- [ ] traded mockmon?



### This is supposed to be a game
- [ ] start game, end game condition
- [ ] display options to user
- [ ] user control over outcome - get user choice
- [ ] meanning full progression path
- [ ] more than one progerssion path
- [ ] none linear progression path
- [ ] can data be saved and loaded?

### Controller stuff
pretend this is an actual gameboy
- [ ] dpad, action, cancel, start select

## Testing?
can i use automated testing?
- [x] add testing package
- [ ] integrate testing to repository on git
- [x] add actual relevent test
- [ ] learn more about testing and clean the code
- [ ] expand testing to anything we can test
- [x] can tests timeout? how? (if a battle never ends)
- [ ] test damage ranges - somehow account for the possibility of critical hits.

### test db completeness
test that all mockmon, moves and everything is defined and doesn't crash
- [ ] test that all 151 mockmons exist and can be constructed
- [ ] test that all moves (how many?) exist, have a name, can be called without crushing the system.

### test conditions
- [x] testing that burn and poison damage the mockmon
- [x] testing that burn halfs attack
- [x] testing that parlysis halfs speed (can we combine them?)
- [x] testing that light screen and reflect change defences
- [ ] test that haze removes all sorts of stuff and does it job and it's bugs

### test statues
status moves change modifiers properly
- [ ] statues moves - test stats are changed
- [ ] reflect/lightscreen/focus energy?
- [ ] ...TBC

## Dev Ops stuff
stuff that needs to be done, but not concerning the business logic of the mockmon engine.
how the project is built, maintained, tested and maintened.

### compiler stuff
- [ ] \[\[maybe_unused\]\] attributre
- [ ] \[\[nodiscard\]\] attribute, wherever possible.
- [ ] add as many relevent compiler warnings flags:

### Build system
- [x] use cmake to build
- [x] use external packages from package managments
- [ ] figure out how to get packages via cmake
- [ ] have a github flow to run build



### UMLs
- [x] create a location for umls on the repository
- [x] have a tool that process the uml to image
- [ ] battle uml - how a battle operates
- [ ] game driver uml - which modes are availble to use currently
- [ ] classes uml - mockmon, conditions, etc...
- [ ] special moves umls - maybe needed

### Documentation
- [ ] can we auto generate a documentation?


## Development takeaways: Maybe The Real Treasure Was the Lessons We Learned Along the Way
stuff that i should keep in mind for the future
* don't use a std::set of function objects, it won't work becuase there isn't a good way to compare two objects. use vector instead.
* std::transform requries std::back_inserter if it's used to populate a new container
* constexpr requires being defined in Header (.h) file, not cpp file.
* TBC...