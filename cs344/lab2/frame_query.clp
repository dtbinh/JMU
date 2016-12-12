(import QueryFrame)

(deffacts queries
    (query hungry "Are you hungry (yes/no): ")
    (query have-money "Do you have any money (yes/no): ")
)

(defrule ask-query "generic input rule"
    ?q <- (query ?query ?prompt)
  =>    
    (bind ?response (sym-cat(QueryFrame.askQuery ?prompt)) )
    (assert (response ?query ?response)) 
    (retract ?q)   ; remove the query so it's not repeated
  )
  

(reset)
(run)
