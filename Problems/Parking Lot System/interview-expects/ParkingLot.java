package interview.expects;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.locks.ReentrantReadWriteLock;

/**
 * Main parking lot service that manages all levels and parking operations.
 * 
 * SOLID Principles:
 * - Single Responsibility: Manage parking allocation and deallocation
 * - Thread Safe: Uses ReentrantReadWriteLock for concurrent access
 * - No initialization/configuration logic (delegated to builder/factory)
 */
public class ParkingLot {
    private final int parkingLotId;
    private final List<ParkingLevel> levels;
    private final ReentrantReadWriteLock lock = new ReentrantReadWriteLock();

    public ParkingLot(int parkingLotId, List<ParkingLevel> levels) {
        if (levels == null || levels.isEmpty()) {
            throw new IllegalArgumentException("Levels list cannot be null or empty");
        }
        this.parkingLotId = parkingLotId;
        this.levels = new ArrayList<>(levels);
    }

    /**
     * Park a vehicle in the lot.
     * Searches through all levels to find an available spot.
     * 
     * Time Complexity: O(n*m) where n is levels, m is average spots per level
     * But typically: First level has spot → O(m)
     * 
     * @param vehicle Vehicle to park
     * @return Spot if parking successful, null if no spot available
     * @throws IllegalArgumentException if vehicle is null
     */
    public Spot parkVehicle(Vehicle vehicle) {
        if (vehicle == null) {
            throw new IllegalArgumentException("Vehicle cannot be null");
        }

        lock.writeLock().lock();
        try {
            // Search all levels for available spot
            for (ParkingLevel level : levels) {
                Spot availableSpot = level.findAvailableSpot(vehicle);
                
                if (availableSpot != null) {
                    // Try to park (double-check to avoid race condition at boundary)
                    boolean parked = availableSpot.parkVehicle(vehicle);
                    if (parked) {
                        return availableSpot;
                    }
                }
            }

            return null; // No spot available
        } finally {
            lock.writeLock().unlock();
        }
    }

    /**
     * Unpark a vehicle from the lot.
     * 
     * @param spot The spot from which to unpark
     * @return The vehicle that was unparked, or null if spot was empty
     * @throws IllegalArgumentException if spot is null
     */
    public Vehicle unparkVehicle(Spot spot) {
        if (spot == null) {
            throw new IllegalArgumentException("Spot cannot be null");
        }

        lock.writeLock().lock();
        try {
            // Verify spot belongs to this parking lot
            if (spot.getLevelId() < 0 || spot.getLevelId() >= levels.size()) {
                throw new IllegalArgumentException("Invalid spot - not in this parking lot");
            }

            return spot.unparkVehicle();
        } finally {
            lock.writeLock().unlock();
        }
    }

    /**
     * Get real-time availability of parking spots by vehicle type.
     * 
     * @return Map of VehicleType to count of available spots
     */
    public Map<VehicleType, Integer> getAvailableSpots() {
        lock.readLock().lock();
        try {
            Map<VehicleType, Integer> availability = new HashMap<>();
            
            for (ParkingLevel level : levels) {
                for (VehicleType type : VehicleType.values()) {
                    int available = level.getAvailableSpotCount(type);
                    if (available > 0) {
                        availability.put(type, 
                            availability.getOrDefault(type, 0) + available);
                    }
                }
            }
            
            return availability;
        } finally {
            lock.readLock().unlock();
        }
    }

    /**
     * Check if a spot is available for a vehicle type
     */
    public boolean hasAvailableSpot(VehicleType vehicleType) {
        if (vehicleType == null) {
            throw new IllegalArgumentException("Vehicle type cannot be null");
        }

        lock.readLock().lock();
        try {
            return getAvailableSpots().getOrDefault(vehicleType, 0) > 0;
        } finally {
            lock.readLock().unlock();
        }
    }

    /**
     * Get total number of spots for a vehicle type
     */
    public int getTotalSpots(VehicleType vehicleType) {
        if (vehicleType == null) {
            throw new IllegalArgumentException("Vehicle type cannot be null");
        }

        lock.readLock().lock();
        try {
            int total = 0;
            for (ParkingLevel level : levels) {
                total += level.getTotalSpotCount(vehicleType);
            }
            return total;
        } finally {
            lock.readLock().unlock();
        }
    }

    /**
     * Get occupancy percentage
     */
    public double getOccupancyPercentage() {
        lock.readLock().lock();
        try {
            int totalCapacity = 0;
            int totalOccupied = 0;

            for (ParkingLevel level : levels) {
                totalCapacity += level.getTotalCapacity();
                totalOccupied += level.getOccupiedCount();
            }

            return totalCapacity == 0 ? 0 : (totalOccupied * 100.0) / totalCapacity;
        } finally {
            lock.readLock().unlock();
        }
    }

    /**
     * Check if parking lot is full
     */
    public boolean isFull() {
        return getAvailableSpots().isEmpty();
    }

    public int getParkingLotId() {
        return parkingLotId;
    }

    public int getNumberOfLevels() {
        return levels.size();
    }

    @Override
    public String toString() {
        return String.format("ParkingLot{id=%d, levels=%d, occupancy=%.1f%%}",
                parkingLotId, levels.size(), getOccupancyPercentage());
    }
}
