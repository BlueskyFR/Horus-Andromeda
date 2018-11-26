#ifndef TARGETMISSILE_H_INCLUDED
#define TARGETMISSILE_H_INCLUDED

void initTargetMissile(TargetMissile &targetMissile);
void collidesWithTargetMissile(Spaceship &spaceship, TargetMissile &targetMissile);
void updateTargetMissile(RenderWindow &game, Spaceship &spaceship, TargetMissile &targetMissile);
void collidesWithTargetMissile(Spaceship &spaceship, TargetMissile &targetMissile);
void collidesWithTargetMissile(Missile &missile, TargetMissile &targetMissile);

#endif // TARGETMISSILE_H_INCLUDED
