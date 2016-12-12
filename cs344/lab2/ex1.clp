/*
 * ex1.clp
 * R.Grove
 * Jan 30, 2014
 */


/* define initial facts */
(deffacts working-memory
    (hungry no)
  )


/* define the rules */
(defrule pizza ""
    (hungry yes)
  =>
    (assert (outcome "Order pizza."))
  )

(defrule library ""
    (hungry no)
  =>
    (assert (outcome "Go to the Library."))
  )
  
  
/* display the outcome at the end */
(defrule showOutcome "print the outcome"
    (outcome ?o)
  =>
    (printout t crlf "Outcome: " ?o crlf crlf)
  )


/* initialize and execute the program */
(reset)
(run)

