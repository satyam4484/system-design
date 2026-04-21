package interview.expects;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Represents a single level/floor in the parking lot.
 * Manages multiple parking spots on this level.
 * 
 * Thread Safety: Uses ReentrantReadWriteLock for concurrent access
 */
public class ParkingLevel {
    private final int levelId;
    private final List<Spot> spots;
    private final ReentrantReadWriteLock lock = new ReentrantReadWriteLock();

    public ParkingLevel(int levelId, List<Spot> spots) {
        if (spots == null || spots.isEmpty()) {
            throw new IllegalArgumentException("Spots list cannot be null or empty");
        }
        this.levelId = levelId;
        this.spots = new ArrayList<>(spots);
    }

    /**
     * Find an available spot for a vehicle.
     * Returns the first empty spot that matches the vehicle type.
     * 
     * Time Complexity: O(n) where n is number of spots on this level
     * 
     * @param vehicle Vehicle to find a spot for
     * @return A suitable empty spot, or null if none available
     */
    public Spot findAvailableSpot(Vehicle vehicle) {
        if (vehicle == null) {
            throw new IllegalArgumentException("Vehicle cannot be null");
        }

        lock.readLock().lock();
        try {
            for (Spot spot : spots) {
                if (spot.isEmpty() && spot.getVehicleType() == vehicle.getType()) {
                    return spot;
                }
            }
            return null;
        } finally {
            lock.readLock().unlock();
        }
    }

    /**
     * Get count of available spots for a vehicle type
     */
    public int getAvailableSpotCount(VehicleType vehicleType) {
        lock.readLock().lock();
        try {
            int count = 0;
            for (Spot spot : spots) {
                if (spot.isEmpty() && spot.getVehicleType() == vehicleType) {
                    count++;
                }
            }
            return count;
        } finally {
            lock.readLock().unlock();
        }
    }

    /**
     * Get total spots of a type on this level
     */
    public int getTotalSpotCount(VehicleType vehicleType) {
        lock.readLock().lock();
        try {
            int count = 0;
            for (Spot spot : spots) {
                if (spot.getVehicleType() == vehicleType) {
                    count++;
                }
            }
            return count;
        } finally {
            lock.readLock().unlock();
        }
    }

    /**
     * Get total capacity of this level
     */
    public int getTotalCapacity() {
        return spots.size();
    }

    /**
     * Get number of occupied spots
     */
    public int getOccupiedCount() {
        lock.readLock().lock();
        try {
            int count = 0;
            for (Spot spot : spots) {
                if (!spot.isEmpty()) {
                    count++;
                }
            }
            return count;
        } finally {
            lock.readLock().unlock();
        }
    }

    public int getLevelId() {
        return levelId;
    }

    @Override
    public String toString() {
        return String.format("Level{id=%d, capacity=%d, occupied=%d}",
                levelId, getTotalCapacity(), getOccupiedCount());
    }
}
