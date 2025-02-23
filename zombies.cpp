while (time_left > 0) {
    List<Move> strategies = new ArrayList<>();  // This will store all possible moves and corresponding scores
    
    for (int i = 0; i < simulations_per_round; i++) {
        List<Human> humans = initialHumans;      // Keep a copy of the original humans list for each simulation
        List<Zombie> zombies = initialZombies;  // Keep a copy of the original zombies list for each simulation
        
        int round = 0;
        while (round++ < rounds_per_simulation && !humans.isEmpty()) {
            Move strategy = new Move(characterX, characterY);
            
            for (Zombie z : zombies) {
                Position bestPosition = strategy.getBestPosition(z.x, z.y, humans);  // This function should return the best position to move to based on your current strategy
                
                if (!bestPosition.equals(characterPosition)) {  // Only update character's position if necessary
                    strategy.addMove(bestPosition);
                    characterX = bestPosition.x;
                    characterY = bestPosition.y;
                    
                    zombies = simulateZombieMoves(zombies, z.x, z.y, humans);  // This function should return a list of updated positions for the zombies based on their move rules (not implemented in this snippet)
                }
            }
        }
        
        strategies.add(strategy);  // Add the final strategy to the list
    }
    
    Move bestStrategy = Collections.max(strategies, Comparator.comparingInt(Move::getScore));  // Choose the move with the highest score (not implemented in this snippet)
    characterX = bestStrategy.x;
    characterY = bestStrategy.y;
    
    time_left--;  // Decrease remaining time by one second
}