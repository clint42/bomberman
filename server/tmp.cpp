// see ressources/info.txt


addBomb() {
  ScopedLock;
  if (bombQueue.empty() == true) {
    bombQueue.push(bomb);
    sem_timedwait(); // temps pour que ca explose
    // normalement c'est pas bloquant
  } else {
    bombQueue.push(bomb);
  }
}

getEventToTreat() {
  ScopedLock;

  if (bombQueue.empty() == false && sem_trylock() == true) {
    // c'est qu'une bomb a fini sa minuterie et doit exploser
    // quand on depush la premier, ne pas oublier de refaire un timewait pour la suivante avec le temps restant pour elle
    sem_delock(); // ne pas oublier
  } else {
    // je m'occupe des evenements 'basiques' qu'il y a dans la eventQueue
  }

}
