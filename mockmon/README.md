# MOCKMON

A small project that I can be motivated to work on. A simple version of a battling game. The user (player) will control mock-monsters (mockmons) and battle the computer in a manner similar to the famoues game. 

## Tasks and Stages

- [ ] Basic program structure
- [x] Player choice modules - allow the user to choose an action
- [x] Create the minimal mockmon class (entity)
- [x] The most simple battle possible - the user has a mockmon and needs to choose the correct option to win
- [x] Design minimal enntities for moves (attacks) and mockmon stats
- [ ] ... TBC

### Mockmon battle mock

#### basics
- [x] a battle with a win / lose conditions
- [x] user can choose actions vs opponent
- [ ] moves that do something and moves that fail
- [x] opponent can do something against user
- [x] moves effect mockmon stats rather than directly the outcome
- [ ] damage ranges
- [ ] two turn moves
- [ ] moves that block/protect against other moves
- [ ] moves that are dependent on status/condition
- [ ] unique moves (mimic, metronome, mirror move, counter)
- [ ] mockmon stats effect the battle outcome
- [x] critical hits
- [x] moves can hit or miss
- [ ] moves can cause status effect
- [ ] moves are effected by stats (accuracy, power)
- [ ] status effects (poison, sleep, confision, etc...)
- [x] the type system! super, normal and not very effective!
- [ ] ... TBC battles are between trainers

#### conditions
- [ ] inflict condition
- [ ] remove condition
- [ ] conditions can't be inflicted based on typing
- [ ] conditions go away after x turns...
- [ ] conditions go away after haze or some other move
- [ ] voltaile contions - bind, flinch, recharging?, semi invurnable?
- [ ] Gen 1 synergy of toxic, burn, leech seed with each other.
- [ ] which conditions work with each other and which are cancelled?
- [ ] which conditions work with moves special effects (dig, charging/recharging)?

##### burn
- [ ] inflict damage
- [ ] doesn't effect fire types
- [ ] halfs phyiscal moves

##### frozen
- [ ] can't move
- [ ] doesn't effect ice types
- [ ] thawed by fire attacks (and other attacks?)

##### paralyzed
- [ ] a chance to not move
- [ ] speed reduction
- [ ] can be caused by different types of attacks, and mockmon of the same type aren't effected by it.

##### poison
- [ ] inflict damage
- [ ] doesn't effect poison types, and maybe steel types.

###### badly poison (toxic)
- [ ] badly poison increases the damgage it inflicts each turn.
- [ ] effects in the outer world

##### sleep
- [ ] won't move
- [ ] chance to wake up
- [ ] maximum sleeping turns
- [ ] effected by dream eater

##### confused
- [ ] chance to hitself with a special attack (no type, no critical hit)
- [ ] chance to snap out of confusion
- [ ] how it works with multiturn abilities


##### leech seed
##### subsitute

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


## Build system
- [ ] use cmake to build
- [x] use external packages from package managments

## Testing?
can i use automated testing?
- [x] add testing package
- [ ] integrate testing to repository on git
- [ ] add actual relevent test

## UMLs
- [ ] create a location for umls on the repository
- [ ] have a tool that process the uml to image
- [ ] battle uml - how a battle operates
- [ ] game driver uml - which modes are availble to use currently
- [ ] classes uml - mockmon, conditions, etc...
- [ ] special moves umls - maybe needed