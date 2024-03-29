#include "entity.h"
#include "steam/steam_api.h"

extern int screenInverted;
extern glm::vec3 hsv;
extern glm::vec2 levelSize;
extern int entityCount;
extern float Width;
extern float Height;

extern void closeProgram();
float Entity::lookAtNearest(std::string targetType) {
    float nearestDist = 100000.0;
    glm::vec2 nearestPos;
    for (Entity * e : *allEntities) {
      if (e->type == targetType) {
        float x;
        x=sqrt(pow(e->pos.x-pos.x, 2) +
               pow(e->pos.z-pos.z, 2));
        if (x < nearestDist) {
          nearestDist = x;
          nearestPos = glm::vec2(e->pos.x,e->pos.z);
        }
      }
    }
    if (nearestDist != 100000.0) {
      nearestPos.x = nearestPos.x - pos.x;
      nearestPos.y = nearestPos.y - pos.z;
      rot.y = -(atan2(nearestPos.y, nearestPos.x))+1.57f;
      rot.x = -1.57f;
      return true;
    }else {
      return false;
    }
}

bool Entity::doesEntityExist(std::string targetType) {
    if (allEntities != nullptr) {
        for (Entity* e : *allEntities) {
            if (e->type == targetType && !e->dead) {
                return true;
            }
        }
        return false;
    }
}
void Entity::setInverted(int i) {
  screenInverted = i;
}
float Entity::getDistanceFromNearest(std::string targetType) {
    float nearestDist = 100000.0;
    if (allEntities == nullptr) {
        return nearestDist;
    }
    for (Entity * e : *allEntities) {
      if (e->type == targetType) {
        float x;
        x=sqrt(pow(e->pos.x-pos.x, 2) +
               pow(e->pos.z-pos.z, 2));
        if (x < nearestDist) {
          nearestDist = x;
        }
      }
    }
    return nearestDist;
}
std::string Entity::getTypeLua() {
    return type;
}
float Entity::getDistanceFromNearestNot(std::string targetType) {
    float nearestDist = 100000.0;
    if (allEntities == nullptr) {
        return nearestDist;
    }
    for (Entity* e : *allEntities) {
        if (e->type != targetType) {
            float x;
            x = sqrt(pow(e->pos.x - pos.x, 2) +
                pow(e->pos.z - pos.z, 2));
            if (x < nearestDist) {
                nearestDist = x;
            }
        }
    }
    return nearestDist;
}
float Entity::getDistanceFromNearestEnt() {
    float nearestDist = 100000.0;
    for (Entity* e : *allEntities) {
        if (e->type != type && e->type != "spawner") {
            float x;
            x = sqrt(pow(e->pos.x - pos.x, 2) +
                pow(e->pos.z - pos.z, 2));
            if (x < nearestDist) {
                nearestDist = x;
            }
        }
    }
    return nearestDist;
}
float Entity::getDistanceFromNearestEnemy() {
    float nearestDist = 100000.0;
    for (Entity* e : *allEntities) {
        if (e->type != type && e->canBeHit == true) {
            float x;
            x = sqrt(pow(e->pos.x - pos.x, 2) +
                pow(e->pos.z - pos.z, 2));
            if (x < nearestDist) {
                nearestDist = x;
            }
        }
    }
    return nearestDist;
}
void Entity::setDamageAnimation(int anim) {
  damageAnim = anim;
}
void Entity::restartCollisionBox() {
  collider.resetBox();
  collider.addBox(glm::vec3(0.0f,0.0f,0.0f),scaleColl*glm::vec3(scale*2.0));
}
void Entity::pushInsideLevel() {
  if (pos.x > levelSize.x) {pos.x = levelSize.x;}
  if (pos.z > levelSize.y) {pos.z = levelSize.y;}

  if (pos.x < -levelSize.x) {pos.x = -levelSize.x;}
  if (pos.z < -levelSize.y) {pos.z = -levelSize.y;}
}
float Entity::getPositionFromNearestX(std::string targetType) {
    float nearestDist = 100000.0;
    glm::vec2 position;
    for (Entity * e : *allEntities) {
      if (e->type == targetType) {
        float x;
        x=sqrt(pow(e->pos.x-pos.x, 2) +
               pow(e->pos.z-pos.z, 2));
        if (x < nearestDist) {
          nearestDist = x;
          position = glm::vec2(e->pos.x,e->pos.z);
        }
      }
    }
    return position.x;
}

float Entity::getPositionFromNearestY(std::string targetType) {
    float nearestDist = 100000.0;
    glm::vec2 position;
    for (Entity * e : *allEntities) {
      if (e->type == targetType) {
        float x;
        x=sqrt(pow(e->pos.x-pos.x, 2) +
               pow(e->pos.z-pos.z, 2));
        if (x < nearestDist) {
          nearestDist = x;
          position = glm::vec2(e->pos.x,e->pos.z);
        }
      }
    }
    return position.y;
}
void Entity::Shake(float amount) {
  auto camera = get<CameraComponent>();
  if (camera != NULL) {
      camera->Shake(amount);
  }
  else {
      std::cout << "ERROR: entity does not have a camera component\n";
  }
}
void Entity::isFirstPerson(bool firstPerson) {
	auto camera = get<CameraComponent>();
	camera->isFirstPerson = firstPerson;
}

void Entity::setFOV(float FOV) {
    auto camera = get<CameraComponent>();
    if (camera != NULL) {
      camera->setFOV(FOV);
    }
}

int Entity::getAnimFrame() {
    auto graphics = get<GraphicsComponent>();
    return graphics->frame;
}
void Entity::playDamageAnimation() {
    auto graphics = get<GraphicsComponent>();
    graphics->playAnim(damageAnim);
}
void Entity::playAnimation(int id) {
    auto graphics = get<GraphicsComponent>();
    graphics->playAnim(id);
}

void Entity::spawnEntity(std::string name, float x, float y) {
    spawnedEntityData.push_back(SpawnData(name, glm::vec2(x,y)));
}

void Entity::killProgram() {
    closeProgram();
}

// bool Entity::GetCollisionWithPoints() {
//     bool projColl = projColliding;
//     if (projColl) {
//       std::cout << "COLLISION SUCCESS..." << '\n';
//     }
//     return projColl;
// }

void Entity::kill() {
    dead = true;
    killed = true;
    collider.body->RemoveAllBoxes();
    auto projc = get<ProjectileComponent>();
    if (projc != NULL) {
      for (Projectile * o : projc->objects) {
        delete o;
      }
      projc->objects.clear();
    }
}

float Entity::getPlayerDistance() {
    float x;
    x=sqrt(pow(enemyTarget.x-pos.x, 2) +
           pow(enemyTarget.y-pos.z, 2));
    return x;
}

void Entity::write(const std::string& str) {
    std::cout << str << '\n';
}

void Entity::setScale(float scale) {
    this->scale = scale;
}

float Entity::random(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float range = max-min;
    return (random*range) + min;
}

int Entity::randomInt(int min, int max) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float range = max - min;
    return (int) (random * range) + min;
}

void Entity::lookAtPlayer() {
    glm::vec2 targetPos = enemyTarget;
    targetPos.x = targetPos.x - pos.x;
    targetPos.y = targetPos.y - pos.z;
    float targetAngle = RADS_TO_DEGS(-(atan2(targetPos.y, targetPos.x))+1.57f);
    float rotDegs = RADS_TO_DEGS(rot.y);
    rotDegs = targetAngle;
    rot.y = DEGS_TO_RADS(rotDegs);
    rot.x = -1.57f;
    rot.z = -0.0f;
    // std::cout << "target is " << targetAngle << " abs is " << std::abs(rotDegs-targetAngle) << " current rotation: " << rotDegs << std::endl;
}

void Entity::copyPlayerRot() {
    for (Entity* e : *allEntities) {
        if (e->type == "player") {
            rot.y = e->rot.y;
            float angle = e->getForward().y;
            float degrees = 180 * angle / 3.1415f;
            int val = (int)(360.0f + round(degrees)) % 360;
            rot.y = (float)val;
            std::cout << angle << "\n";
        }
        break;
    }
}

void Entity::lookAt(float x, float y) {
    glm::vec2 targetPos = glm::vec2(x,y);
    targetPos.x = targetPos.x - pos.x;
    targetPos.y = targetPos.y - pos.z;
    float targetAngle = -(atan2(targetPos.y, targetPos.x))+1.57f;
    if (std::abs(rot.y-targetAngle) > 0.05) {
      if (targetAngle>rot.y) {
        rot.y += 0.02;
      }else {
        rot.y -= 0.02;
      }
    }
    rot.x = -1.57f;
}

void Entity::Strafe(float amount) {
    pos += glm::cross(glm::vec3(0.0f,1.0f,0.0f), getForward()) * amount * speedModifier;
}

void Entity::moveForward(float amount) {
    pos.x += getForward().x * amount * speedModifier;
    pos.z += getForward().z * amount * speedModifier;
   // collider.setVelocity(glm::vec3(getForward().x * amount, 0.0, ))
}

void Entity::moveBackward(float amount) {
    pos.x = pos.x-(cos(rot.y*180/3.14)*-amount * speedModifier);
    pos.z = pos.z-(sin(rot.y*180/3.14)*-amount * speedModifier);
    //pos.x += getForward().x * -amount * speedModifier;
    //pos.z += getForward().z * -amount * speedModifier;
}

void Entity::setAnimation(int id) {
    auto graphics = get<GraphicsComponent>();
    graphics->setAnimID(id);
    graphics->object.lastAnimation = id;
}

int Entity::getAnimation() {
    auto graphics = get<GraphicsComponent>();
    return graphics->getAnimID();
}

void Entity::setPos(float x, float y, float z) {
    if (type == "player") {
      auto cameraC = get<CameraComponent>();
      cameraC->setPos(glm::vec3(x,y,z));
    }else {
      pos = glm::vec3(x,y,z);
    }
}

float Entity::getX() {
    return pos.x;
}

float Entity::getY() {
    return pos.y;
}

float Entity::getZ() {
    return pos.z;
}

void Entity::setColorFlash(float r, float g, float b, float a) {
    auto graphics = get<GraphicsComponent>();
    auto sgraphics = get<StaticGraphicsComponent>();
    if (graphics != NULL) {
        graphics->setColorFlash (glm::vec4(r, g, b, a));
    }else if (sgraphics != NULL) {
      sgraphics->setColor(glm::vec4(r,g,b,a));
    }else {
      std::cout << "COULD NOT SET COLOR OF ENTITY OF TYPE: " << type << std::endl;
    }
}
void Entity::setColor(float r, float g, float b, float a) {
    auto graphics = get<GraphicsComponent>();
    auto sgraphics = get<StaticGraphicsComponent>();
    if (graphics != NULL) {
        graphics->setColor(glm::vec4(r, g, b, a));
    }
    else if (sgraphics != NULL) {
        sgraphics->setColor(glm::vec4(r, g, b, a));
    }
    else {
        std::cout << "COULD NOT SET COLOR OF ENTITY OF TYPE: " << type << std::endl;
    }
}
bool Entity::isPlayer() {
  return (type == "player");
}
float Entity::getKeyDirectionX() {
    SDL_PumpEvents();
    keys = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));
    float direction = 0.0f;
    if (keys[SDL_SCANCODE_A]){
      direction -= 1.0f;
    }
    if (keys[SDL_SCANCODE_D]){
      direction += 1.0f;
    }
    return direction;
}

float Entity::getKeyDirectionY() {
    SDL_PumpEvents();
    keys = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));
    float direction = 0.0f;
    if (keys[SDL_SCANCODE_S]){
      direction -= 1.0f;
    }
    if (keys[SDL_SCANCODE_W]){
      direction += 1.0f;
    }
    return direction;
}

std::string Entity::getKeyPressed() {
    return keypressed;
}

void Entity::TopDownUpdate() {
    setPos(0.0f,250.0f,0.0f);
    keys = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));
    if (allEntities != NULL) {

    }
    if (keys[SDL_SCANCODE_LSHIFT]){
      keypressed = "LSHIFT";
    }
    if (keys[SDL_SCANCODE_ESCAPE]){
      keypressed = "ESCAPE";
    }
    if (keys[SDL_SCANCODE_LCTRL]) {
      keypressed = "LCTRL";
    }
    if (keys[SDL_SCANCODE_TAB]) {
      keypressed = "TAB";
    }
    if (keys[SDL_SCANCODE_SPACE]) {
      keypressed = "SPACE";
    }
    SDL_PollEvent( &e );
}

void Entity::FPSControllerUpdate(float speed) {
    auto cameraC = get<CameraComponent>();
//    pos = cameraC->getCamera().m_position;
    cameraC->lastX = cameraC->x;
    cameraC->lastY = cameraC->y;
    SDL_PumpEvents();
    keys = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));
    glm::vec3 startPos;
    startPos = cameraC->getCamera().m_position;
    SDL_PollEvent( &e );
    SDL_GetRelativeMouseState( &cameraC->x, &cameraC->y );


    float cameraMulX = 800 / Width;
    float cameraMulY = 600 / Height;
    cameraC->getCamera().RotateY(((float)-cameraC->x/300.0f)*cameraMulX);
    cameraC->getCamera().Pitch(((float)cameraC->y/300.0f)*cameraMulY);
    std::string lastKey = keypressed;
//    playerVel = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 startPlayerVel = glm::vec3(0.0f,0.0f,0.0f);
    float deltaTime = 1/FPS;
    float multiplier = 1;
    if (keys[SDL_SCANCODE_S]){
      pos += cameraC->getCamera().m_forward * -speed * multiplier;
      moved = true;
    }
    if (keys[SDL_SCANCODE_W]){
      pos += cameraC->getCamera().m_forward*speed * multiplier;
      moved = true;
    }
    if (keys[SDL_SCANCODE_A]){
      pos += glm::cross(cameraC->getCamera().m_up, cameraC->getCamera().m_forward) * speed * multiplier;
      moved = true;
    }
    if (keys[SDL_SCANCODE_D]){
      pos += glm::cross(cameraC->getCamera().m_up, cameraC->getCamera().m_forward) * -speed * multiplier;
      moved = true;
    }
    if (startPos == pos) {
      collider.resetVelocity();
    }
    /*glm::vec3 cameraAngle = AnglesFromVectors(cameraC->getCamera().m_forward, cameraC->getCamera().m_up);
    std::cout << "cameraAngle X:" << cameraAngle.x << " Y:" << cameraAngle.y << " Z:" << cameraAngle.z << "\n";
    if (cameraAngle.x < 90) {
        cameraC->getCamera().m_up = lastCameraUp;
    }*/
    lastCameraUp = cameraC->getCamera().m_up;
//    pos = cameraC->getCamera().m_position;
    cameraC->getCamera().m_position.y = 10.0f;
}
void Entity::UpdateKeyPresses() {
  SDL_PollEvent( &e );
  keys = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));
  std::string tempKeyPressed = "";
  if (keys[SDL_SCANCODE_ESCAPE]){
    tempKeyPressed = "ESCAPE";
  }
  else if (keys[SDL_SCANCODE_LCTRL]) {
    tempKeyPressed = "LCTRL";
  }
  else if (keys[SDL_SCANCODE_TAB]) {
    tempKeyPressed = "TAB";
  }
  else if (keys[SDL_SCANCODE_SPACE]) {
    tempKeyPressed = "SPACE";
  }
  else if (keys[SDL_SCANCODE_LSHIFT]){
    tempKeyPressed = "LSHIFT";
  }
  else if (keys[SDL_SCANCODE_Q]) {
      tempKeyPressed = "Q";
  }
  else if (keys[SDL_SCANCODE_RETURN]) {
      tempKeyPressed = "ENTER";
  }
  moveDirection = glm::vec2(0.0, 0.0);
  if (keys[SDL_SCANCODE_W]) {
      moveDirection.y += 1.0;
  }
  if (keys[SDL_SCANCODE_A]) {
      moveDirection.x -= 1.0;
  }
  if (keys[SDL_SCANCODE_S]) {
      moveDirection.y -= 1.0;
  }
  if (keys[SDL_SCANCODE_D]) {
      moveDirection.x += 1.0;
  }

  arrowDirection = glm::vec2(0.0, 0.0);
  if (keys[SDL_SCANCODE_UP]) {
      arrowDirection.y += 1.0;
  }
  if (keys[SDL_SCANCODE_LEFT]) {
      arrowDirection.x -= 1.0;
  }
  if (keys[SDL_SCANCODE_DOWN]) {
      arrowDirection.y -= 1.0;
  }
  if (keys[SDL_SCANCODE_RIGHT]) {
      arrowDirection.x += 1.0;
  }
  if (tempKeyPressed != keypressed) {
    keyCount++;
    if (keyCount > 3) {
      keyCount = 0;
      keypressed = tempKeyPressed;
    }
  }
}
float Entity::getHP() {
    return hp;
}

void Entity::setHP(float hp) {
    this->hp = hp;
    if (maxHP == -1.0) {
        maxHP = hp;
    }
    bar.setValue(hp / maxHP);
}

void Entity::addCounter(int start) {
    counters.push_back(start);
}

bool Entity::updateCounter(int counter,int end) {
    counters[counter]++;
    if (counters[counter]>=end) {
      counters[counter]=0;
      return true;
    }else {
      return false;
    }
}

int Entity::getCount() {
    return count;
}

void Entity::setCount(int count) {
    this->count=count;
}
void Entity::FireInstant() {
    auto projC = get<ProjectileComponent>();
    if (projC != nullptr) {
        projC->Fire(glm::vec2(pos.x, pos.z), getForward());
    }
}
void Entity::FireMultiple(int num) {
    auto projC = get<ProjectileComponent>();
    if (projC != nullptr) {
        projC->FireMultiple(glm::vec2(pos.x, pos.z), getForward(), num);
    }
}
bool Entity::Fire() {
    if (!dead) {
      auto projC = get<ProjectileComponent>();
      if (type != "player") {
        if (projC->Fire(glm::vec2(pos.x,pos.z),getForward())) {
          return true;
        }else {
          return false;
        }
      }else {
        if (projC->Fire(glm::vec2(pos.x,pos.z),getCamForward())) {
          return true;
        }else {
          return false;
        }
      }
    }
}
void Entity::setGlobalFrozen(bool f) {
    globalFrozen = f;
}
Entity* Entity::getNearestEntWithName(std::string entityName) {
    Entity * nearest = nullptr;
    float dist = 10000.0f;
    if (allEntities == nullptr) {
        return nearest;
    }
    for (Entity * e : *allEntities) {
      if (e->type == entityName) {
        if (dist > getDistanceBetweenTwoPoints(glm::vec2(pos.x,pos.z), glm::vec2(e->pos.x,e->pos.z))) {
          nearest = e;
          dist = getDistanceBetweenTwoPoints(glm::vec2(pos.x,pos.z), glm::vec2(e->pos.x,e->pos.z));
        }
      }
    }

    if (nearest == nullptr) {
        return NULL;
    }
    else {
        return nearest;
    }
}

bool Entity::getGlobalFrozen() {
    return globalFrozen;
}

void Entity::setFrozen(bool f) {
    frozen = f;
}

bool Entity::getFrozen() {
    return frozen;
}

float Entity::getDistanceBetweenTwoPoints(glm::vec2 pos1, glm::vec2 pos2) {
  float x_diff = pos1.x - pos2.x;
  float y_diff = pos1.y - pos2.y;
  return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}

void Entity::setAnimationTag(std::string tag, int animation) {
  auto gfxc = get<GraphicsComponent>();
  if (gfxc != NULL) {
    gfxc->setAnimationWithTag(tag,animation);
  }
}

void Entity::playAnimationTag(std::string tag) {
  auto gfxc = get<GraphicsComponent>();
  if (gfxc != NULL) {
    gfxc->playAnimTag(tag);
  }
}
void Entity::resetFrame() {
    auto gfxc = get<GraphicsComponent>();
    if (gfxc != NULL) {
        gfxc->resetFrame();
    }
}
bool Entity::isAnimationPlaying(std::string tag) {
  auto gfxc = get<GraphicsComponent>();
  if (gfxc != NULL) {
    return gfxc->isAnimationPlaying(tag);
  }
}

float Entity::getLastX() {return lastPos.x;}
float Entity::getLastY() {return lastPos.y;}
float Entity::getLastZ() {return lastPos.z;}

float Entity::getDistanceBetweenTwoPointsAPI(float x, float y, float x2, float y2) {
  float x_diff = x - x2;
  float y_diff = y - y2;
  return std::sqrt(x_diff * x_diff + y_diff * y_diff);
}
void Entity::setCollisionBox(float width, float height, float length) {
    Min.x = -width;
    Min.y = -height;
    Min.z = -length;
    Max.x = width;
    Max.y = height;
    Max.z = length;
    scaleColl = glm::vec3(width,length,height);
}
void Entity::Delay(int milliseconds) {
    SDL_Delay(milliseconds);
}
void Entity::setUIText(std::string text) {
    textPointer = new std::string(text);
    modText = true;
}
Entity* Entity::getNearestEntity() {
    Entity* nearest = nullptr;
    float dist = 10000.0f;
    for (Entity* e : *allEntities) {
        if (e->type != type) {
            if (dist > getDistanceBetweenTwoPoints(glm::vec2(pos.x, pos.z), glm::vec2(e->pos.x, e->pos.z))) {
                nearest = e;
                dist = getDistanceBetweenTwoPoints(glm::vec2(pos.x, pos.z), glm::vec2(e->pos.x, e->pos.z));
            }
        }
    }
    if (nearest == nullptr) {
        return NULL;
    }
    else {
        std::cout << "got nearest\n";
        return nearest;

    }
}
void Entity::damageNearest(int damage) {
    Entity* nearest = nullptr;
    float dist = 10000.0f;
    for (Entity* e : *allEntities) {
        if (e->type != type) {
            if (dist > getDistanceBetweenTwoPoints(glm::vec2(pos.x, pos.z), glm::vec2(e->pos.x, e->pos.z))) {
                nearest = e;
                dist = getDistanceBetweenTwoPoints(glm::vec2(pos.x, pos.z), glm::vec2(e->pos.x, e->pos.z));
            }
        }
    }
    Hit(damage, nearest);
}
int Entity::damageWithinADistance(int damage, int distance) {
    int x = 0;
    for (Entity* e : *allEntities) {
        if (e->type != type && e->canBeHit == true) {
            if (distance > getDistanceBetweenTwoPoints(glm::vec2(pos.x, pos.z), glm::vec2(e->pos.x, e->pos.z))) {
                Hit(damage, e);
                x++;
            }
        }
    }
    return x;
}
void Entity::damageNearestEnt(std::string ent, int damage) {
    Entity* nearest = nullptr;
    float dist = 10000.0f;
    for (Entity* e : *allEntities) {
        if (e->type == ent) {
            if (dist > getDistanceBetweenTwoPoints(glm::vec2(pos.x, pos.z), glm::vec2(e->pos.x, e->pos.z))) {
                nearest = e;
                dist = getDistanceBetweenTwoPoints(glm::vec2(pos.x, pos.z), glm::vec2(e->pos.x, e->pos.z));
            }
        }
    }
    Hit(damage, nearest);

}
void Entity::playSound(std::string file) {
    sound.setFile(file);
    sound.play();
}
void Entity::setBrightness(float b) {
    brightness = b;
}
float Entity::getProjCount() {
    auto projc = get<ProjectileComponent>();
    return projc->delayCount;
}
void Entity::setProjCount(float count) {
    auto projc = get<ProjectileComponent>();
    projc->delayCount = count;
}
void Entity::Emit(int num, float r, float g, float b, float a) {
    emitter.addParticles(num, glm::vec3(pos.x, pos.y + 6.0, pos.z), glm::vec4(r,g,b,a));
}
void Entity::setRot(float x, float y, float z) {
    rot = glm::vec3(x,y,z);
}
void Entity::setPlayerTag(std::string tag) {
    playerTag = tag;
}
std::string Entity::getPlayerTag() {
    return playerTag;
}
void Entity::setHue(float hue) {
    hsv.x = hue;
}
void Entity::setSaturation(float saturation) {
    hsv.y = saturation;
}
void Entity::setValue(float value) {
    hsv.z = value;
}
void Entity::setParticleSpread(float spread) {
    emitter.Randomness = spread;
}
void Entity::setParticleModel(std::string model) {
    emitter.setModel(model);
}
void Entity::setCollide(bool enable) {
    
    if (enable) {
        collider.body->SetToAwake();
    }
    else {
        collider.body->SetToSleep();
    }
}
std::string Entity::getDefaultAnim() {
    auto graphicsC = get<GraphicsComponent>();
    if (graphicsC != NULL) {
        return graphicsC->defaultAnim;
    }
}
int Entity::getAnimationID(std::string tag) {
    auto graphicsC = get<GraphicsComponent>();
    if (graphicsC != NULL) {
        return graphicsC->AnimationTags[tag];
    }
}
bool Entity::hasAnimation(std::string anim) {
    auto graphicsC = get<GraphicsComponent>();
    if (graphicsC != nullptr) {
        return (graphicsC->AnimationTags.count(anim) > 0);
    }
}
void Entity::showHealth(bool value) {
    showHP = value;
}
void Entity::setHPColor(float r, float g, float b) {
    bar.setColor(glm::vec4(r,g,b,1.0));
}
void Entity::setText(std::string tag, std::string text, float x, float y) {
    auto guiC = get<GUIComponent>();
    if (guiC != NULL) {
        guiC->setText(tag, text, glm::vec2(x, y), currentColor);
    }
    else {
        std::cout << "can't draw gui without GUI Component\n";
    }
    
}
int Entity::getEntityCount() {
    return entityCount;
}
void Entity::setTextColor(float r, float g, float b, float a) {
    currentColor = glm::vec4(r, g, b, a);
}
void Entity::addAbility(std::string ability, std::string description) {
    playerAbilities.push_back(ability);
    playerAbilitiesDesc.push_back(description);
}
std::string Entity::getAbility(int val) {
    return playerAbilities[val];
}
std::string Entity::getAbilityDescription(int val) {
    return playerAbilitiesDesc[val ];
}
void Entity::setScreenColor(glm::vec4 ScreenColor) {
    screenColor = ScreenColor;
}

void Entity::setDrawScene(bool val) {
    drawScene = val;
}
void Entity::stopProgram() {
    closeProgram();
}
void Entity::setSpread(float s) {
    auto projC = get<ProjectileComponent>();
    if (projC != nullptr) {
        projC->setSpread(s);
    }
}
void Entity::setProjColor(float r, float g, float b, float a) {
    auto projC = get<ProjectileComponent>();
    if (projC != nullptr) {
        projC->setColor(glm::vec4(r, g, b, a));
    }
}
void Entity::setProjDelay(int del) {
    auto projC = get<ProjectileComponent>();
    if (projC != nullptr) {
        projC->delay = del;
    }
}
void Entity::setObjectPos(float x, float y, float z) {
    auto objc = get<ObjectComponent>();
    if (objc != nullptr) {
        objc->setPos(glm::vec3(x, y, z));
    }
}
void Entity::setObjectScale(float sc) {
    auto objc = get<ObjectComponent>();
    if (objc != nullptr) {
        objc->setScale(glm::vec3(sc));
    }
}
void Entity::setObjectColor(float r, float g, float b, float a) {
    auto objc = get<ObjectComponent>();
    if (objc != nullptr) {
        objc->setColor(glm::vec4(r, g, b, a));
    }
}
void Entity::setEnemyTarget(float x, float y) {
    enemyTarget = glm::vec2(x, y);
}
float Entity::getObjectX() {
    auto objc = get<ObjectComponent>();
    if (objc != nullptr) {
        return objc->getPos().x;
    }
}
float Entity::getObjectY() {
    auto objc = get<ObjectComponent>();
    if (objc != nullptr) {
        return objc->getPos().y;
    }
}
float Entity::getObjectZ() {
    auto objc = get<ObjectComponent>();
    if (objc != nullptr) {
        return objc->getPos().z;
    }
}

void Entity::setUICam(bool val) {
    auto graphicsC = get<GraphicsComponent>();
    if (graphicsC != nullptr) {
        graphicsC->useUICam = val;
    }
}
void Entity::setDrawUI(bool val) {
    drawUI = val;
}
void Entity::setProjRange(int range) {
    auto projC = get<ProjectileComponent>();
    if (projC != nullptr) {
        projC->setRange(range);
    }
}
void Entity::setTextSize(int textSize) {
    auto guiC = get<GUIComponent>();
    if (guiC != NULL) {
        guiC->setTextSize(textSize);
    }
}
void Entity::setImageTransform(float x, float y, float width, float height) {
    auto guiC = get<GUIComponent>();
    if (guiC != NULL) {
        guiC->setImageTransform(glm::vec2(x,y), glm::vec2(width, height));
    }
}
void Entity::setImage(std::string tag, std::string src) {
    auto guiC = get<GUIComponent>();
    if (guiC != NULL) {
        guiC->setImage(tag, src);
    }
}
void Entity::setImageDraw(std::string tag, bool draw) {
    auto guiC = get<GUIComponent>();
    if (guiC != NULL) {
        guiC->setDraw(tag, draw);
    }
}
void Entity::setMouseCapture(bool value) {
    if (value == true) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    } else {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}
void Entity::setScreenResolution(float width, float height) {
    Width = width;
    Height = height;
    resetCamera = true;
    resetFramebuffer = true;
    resetWindow = true;
    resetText = true;
}
void Entity::setObjectModel(std::string model) {
    auto objC = get<ObjectComponent>();
    if (objC != NULL) {
        objC->object.initObject(model, objC->color, "./res/basicShader", false);
    }
}
int Entity::getHighscore() {
    return getHighScore();
}
void Entity::setHighscore(int val) {
    setHighScore(val);
}
float Entity::sinFunc(float x) {
    return sin(x);
}
void Entity::setAchievement(std::string name) {
    if (SteamUserStats()->SetAchievement(name.c_str()) == true) {
        std::cout << "added achievement\n\n\n\n\n\n\n\n\n\n";
    }
}
