# MOCKMON

A small project that I can be motivated to work on. A simple version of a battling game. The user (player) will control mock-monsters (mockmons) and battle the computer in a manner similar to the famoues game. 

## Points of intrest
I want to replicate the bugs. over the years, the player community discovered many bugs and glitches in the game, and i wish to see how these might have come into existence. so in some cases I will delibratly have behavior which seems non-sensical. I believe these this bugs were not put in the game intenionally, but were products of software design which was streched beyond what it was intended for, either by the constraints of the availble programming languages or by last minute changes that had to be implemented. therefore, i will try to design this program in a way that those bugs appear organically.


## Tasks and Stages - this will eventuall be the Issues tab

- [ ] Basic program structure
- [x] Player choice modules - allow the user to choose an action
- [x] Create the minimal mockmon class (entity)
- [x] The most simple battle possible - the user has a mockmon and needs to choose the correct option to win
- [x] Design minimal enntities for moves (attacks) and mockmon stats
- [ ] Document code using doxygen standatds(/** /*! ///),
- [ ] ... TBC

### Mockmon battle mock

#### basics
- [x] a battle with a win / lose conditions
- [x] user can choose actions vs opponent
- [ ] moves that do something and moves that fail
- [x] opponent can do something against user
- [x] moves effect mockmon stats rather than directly the outcome
- [ ] damage ranges
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

##### Two turns moves
- [x] moves with charging before hitting - dig, fly, skull bash,sky attack,solar beam,
- [ ] moves with invurnability stage - dig, fly
- [ ] moves with re-charging after hitting - hyperBeam
- [ ] power points consumption - when damage is done
- [ ] interacton with status effects - paused? stopped? what if i hit myself in confusion is pparalyzed
- [ ] weird gen one mechanics


##### Multi turns moves
- [ ] multi turn moves

#### conditions
- [x] inflict condition
- [x] remove condition
- [ ] conditions can't be inflicted based on typing
- [x] conditions go away after x turns...
- [ ] conditions go away after haze or some other move
- [ ] voltaile contions - bind, flinch, recharging?, semi invurnable?
- [ ] Gen 1 synergy of toxic, burn, leech seed with each other.
- [ ] which conditions work with each other and which are cancelled?
- [ ] which conditions work with moves special effects (dig, charging/recharging)?
- [ ] pulsing conditions - conditions that do something each turn (poison,burn, etc...)
- [ ] non-pulsing conditions - conditions that just stick to the mockmon with 'active' effects (light screen, reflect, focus energy)

##### flinch - pulse
- [ ] mockmon won't move
- [ ] only relevent when going 2nd

##### burn - pulse
- [x] inflict damage
- [ ] doesn't effect fire types
- [x] halfs phyiscal moves attacks
- [ ] more gen I shannignas

##### frozen - pulse
- [ ] can't move
- [ ] doesn't effect ice types
- [ ] thawed by fire attacks (and other attacks?)

##### paralyzed - pulse
- [x] a chance to not move
- [x] speed reduction
- [ ] can be caused by different types of attacks, and mockmon of the same type aren't effected by it.
- [ ] more gen I shannignas

##### poison - pulse
- [x] inflict damage
- [ ] doesn't effect poison types, and maybe steel types.
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
- [ ] chance to hitself with a special attack (no type, no critical hit)
- [ ] chance to snap out of confusion
- [ ] how it works with multiturn abilities
- [ ] Gen I glitch where defence is effected by the enemy having reflect (mentioned in the wiki under confusion, not under general glitchs)

##### haze
- [ ] remove some conditions
- [ ] resets status modifiers

##### leech seed
##### subsitute

##### reflect, light screen - non-pulse
- [x] refelct - change physical defence
- [x] light screen - change only special when defending

##### focus energy - non-pulse
- [x] effect critical hit rate
- [x] gen I issues


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

### This is supposed to be a game

- [ ] start game, end game condition
- [ ] display options to user
- [ ] user control over outcome - get user choice
- [ ] meanning full progression path
- [ ] more than one progerssion path
- [ ] none linear progression path
- [ ] can data be saved and loaded?

### Controller stuff
- [ ] dpad, action, cancel, start select

## Dev Ops stuff
stuff that needs to be done, but not concerning the business logic of the mockmon engine.
how the project is built, maintained, tested and maintened.

### Build system
- [ ] use cmake to build
- [x] use external packages from package managments

### Testing?
can i use automated testing?
- [x] add testing package
- [ ] integrate testing to repository on git
- [x] add actual relevent test
- [ ] learn more about testing and clean the code
- [ ] expand testing to anything we can test
- [x] can tests timeout? how? (if a battle never ends)

#### test conditions
- [x] testing that burn and poison damage the mockmon
- [x] testing that burn halfs attack
- [ ] testing that parlysis halfs speed (can we combine them?)
- [x] testing that light screen and reflect change defences
- [ ] test that haze removes all sorts of stuff and does it job and it's bugs


### UMLs
- [x] create a location for umls on the repository
- [x] have a tool that process the uml to image
- [ ] battle uml - how a battle operates
- [ ] game driver uml - which modes are availble to use currently
- [ ] classes uml - mockmon, conditions, etc...
- [ ] special moves umls - maybe needed