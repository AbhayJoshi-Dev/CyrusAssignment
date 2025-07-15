### Assignment submission for Cyrus 365

A Fps demo with enemy spawning through json parsing and health/damage system

#### How to Build:
Project uses Unreal Version 5.6 and written in C++, to build the project
- Right mouse click on the uproject file
- Generate visual studio project files
- open and build the solution


### Features:

#### Json Web request and parsing:
this demo uses unreal's json api to request and parse data from the web. `BoxSpawner.cpp` 's method `SendHttpRequest()` creates the request, and on completing the request it calls `HandleRequestCompleted()` . `ParseBoxData()` parse the data and stores it into the appropriate array which later used for spawning the Boxes.
#### Health/Damage system:
all damageable actors inherit from the `Damageable` interface and override the virtual method `DamageTaken()` virtual method. When `DamageTaken()` is called (e.g., on projectile hit), the actor reduces its health. Once the health reaches zero, the actor destroys itself.
#### Projectile Shooting:
this demo uses projectile base shooting. Projectiles are spawned in front of the weapon and uses `UProjectileMovementComponent` to handle movement.

### Challanges:
Structuring the code efficiently was a key challenge for me during this project.
I'm still learning and improving my ability to write maintainable, modular game code.

### Test Features:

##### requesting / parsing data
You can modify the web JSON to add more objects or types, and the spawner will spawn new boxes dynamically without modifying the game code.

##### gameplay
Basic Movement - use W, A, S and D for basic character movement.
Shooting - left mouse button for firing the projectile.