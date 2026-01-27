1.How I come up wih the idea of doing the project?

It was when I booked the tickets for travelling in the winter break. I input the departure city and arrive city, but I noticed that sometimes thirdparty websites often had a lower base price. This made them look cheaper at first. However, they always have extra charges for things like baggage, insurance, and service fees later. It was confusing to find the true final cost. By contract, airline's official website, the initial price was usually higher, but that price often already included the baggage or insurance fees. The cost was clearer and more straightforward. This is what inspired me to build this project: a simple platform to help users quickly compare the real total cost of flights from all providers.

2.What was my design thinking and source of inspiration?

To change this idea (comparing total costs) into C++ code, I first researched online existing C++ platforms and projects online.

 (here is the link: https://github.com/NishantSinghF11/Flight-Booking-System-project-in-cpp , 
https://github.com/Ashrithvicky/AirlineTicketReservationSystem).
    The link only for inspiration and as a reference for project structure. No single line of code in my project was copied or adapted from these sources.
I carefully examined their file structures and class designs to understand how a larger project is organized. I noticed that these existing projects usually focused on managing simple flight data but failed to effectively handle complex fare types and include all extra fees in the final cost.
Therefore, with my TA Lydia's help, my approach was to: 1. Create a core FlightOrder class that stores all necessary fees (baggage, insurance) 2. Use inheritance and polymorphism to design a "FareType" base class, with "EconomyClass" and "FirstClass" as child classes. 
This allows the program to easily calculate the final price based on the selected fare type.

3.Did I use any concepts beyond the course ?

Yes. When I am designing, I met some problem about invalid input or go back problem. In main.cpp, if the user wanted to go back from a deep selection menu , standard "break"or "continue" commands couldn't perform the "directly jump back to the main step" that I needed. I researched a lot of online C++ resources and discussion forums. Finally, I discovered and used the goto statement.
Here is a useful link: https://www.geeksforgeeks.org/cpp/goto-statement-in-cpp/

4. Where did my data come from?

The mock_flight_data.csv file is a simulation. They are mock data only for my program testing. The variable name(column names) are referenced from a real-world dataset:
 https://rowzero.com/datasets/us-flights-dataset.

5.Any flaws?

Yes. In the FlightOrder class. When a flight object is copied ( like added to the cart), the new and old objects share the same pointer. I spent three full days debugging why the exe program crashed halfway. My professor warned us that very carefully using a raw pointer because it always easily introduces bugs, and the program runs the risk of crashing. While the current project should run normally, I will definitely be more careful when using pointers.