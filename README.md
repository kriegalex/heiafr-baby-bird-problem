# Baby bird problem
A C++ mutex based solution to the baby bird problem as seen in the concurrent programming course

## Statement
A long, long time ago, in a galaxy far, far away, there was a species of birds called Kekekbri. These birds
had an unusual behavior in raising their chicks:

1. The parents fed the chicks by depositing a certain amount (portions) of food in the nest.
2. The nest could contain at most a capacity C of food.
3. To teach the chicks that they must eat all food that is available, all food had to be consumed before
the parents would drop more food in the nest.
4. Parents alternated between hunting and dropping food in the nest. If the nest was not empty, they
waited until the nest was empty before adding food.
5. Occasionally, families shared a nest, so there could have been multiple parents tending the total
brood of chicks. Thus, conceptually, there were any number of parents hunting for food and feeding
the chicks..

Meanwhile, the chicks did what all babies do:

1. Sleep ...
2. Eat (a single portion of food at a time)...
3. ... And produce doo-doo (also known as guano)

You must write a program that simulates the life of these birds, creating multiple parent process, and several
chicks process. The behavior of chicks and parents resembles the situation described by the following
pseudo-code:

    process Chicks(many of them) {          process Parents(at least 1) {
        repeat "baby_iter times" {              repeat "as necessary" {
            sleep();                                hunt();
            get_food();                             deposit_food();
            eat();                                  rest();
            digest_and___();                    }
        }                                   }
    }

Your program will accept the following parameters (default values):

* chicks is the number of chick processes (7);
* baby_iter is the number of iterations a baby chick does before it reaches adulthood and leaves the
nest (53);
* parent_number is the number parents for this simulation (3);
* max_food_size is the maximum portion size a parent brings back from a hunt (5; as fate would
have it, this is the same as the capacity of the nest to contain food described earlier);
* hunting_success_rate represents the success rate a parent has when hunting (30). For
example, a rate of 50% means that half the time, a parent returns with no food. There is no percent
after this number.

To start a simulation with (for example) 17 chicks, 53 iterations per chick, 2 parents, maximum food size 7,
and 30% hunt success rate, the program will be invoked as follows:

    main 17 53 2 7

Note: all arguments are optional, the main class is called Kekekbri, and your program must output on
stdout the line "Simulation has ended, all processes have terminated normally"
at the end of the simulation.
