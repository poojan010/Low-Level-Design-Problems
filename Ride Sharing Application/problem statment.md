
# Ride Sharing Application

### Problem Statement

>#### Ride Sharing application
> Where drivers can offer rides(origin, destination, no of seats), any rider can request rides(origin, destination, no of seats) 
> 
> We need to design interface for user interaction.
> 
> Requirements
> Need to provide system govering classes
>
> System should take as input two or more drivers and a set of riders requesting rides
>
> When the ride closes, show the amount charged to the rider.
> 1. Ride amount if No of seats >= 2 : No of kilometers * No of seats * 0.75 * Amount Charged per KM
> 2. Ride amount if No of seats = 1 : No of kilometers * Amount Charged per KM
>
> Program should take as input two or more drivers and a set of riders requesting rides. Multiple rides can happen simultaneously.
>
> Users should be able to request the system to create, update, withdraw and close rides.
>
> A ride can be created only if there's driver available
>
> You can use either of the programs as a template and build on top of that 
>
> Upgrade the rider to a preferred rider if he has done in more than 10 rides.
> 1. Preferred Rider amount if No of seats >= 2 : No of kilometers * No of seats * 0.5 * Amount Charged per KM 
> 2. Preferred Rider amount if No of seats = 1 : No of kiolmeters * Amount Charged per KM 
