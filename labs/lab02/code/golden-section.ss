;golden-section
(define a 19)(define b 20);19.999995177562162
(define (fun x)
 (set! x (- x (/ 107 108 e)))
 (-
  (* 0.1 (expt x 2))
  (* x (log x))
 )
;     0.1x^2 - xlnx
)
(define eps 0.00001)

(define (golden-section-search a b)
 (let(
      (xmin(if(< a b)(golden-start a b)(golden-start b a )))
     )
     (newline)
     xmin
 )
)
(define (golden-start a b)

 (let(
      (x1 (- b (/ (- b a) mphi)))
      (x2 (+ a (/ (- b a) mphi)))
     )
     (try a b x1 (fun x1) x2 (fun x2))
 )
)

(define mphi (* 0.5 (+ 1(sqrt 5))))

(define (try a b x1 y1 x2 y2)
 (cond((<(abs (- a b))eps)(* (+ a b)0.5))
      (#t (display "+")
          (cond((< y1 y2)(set! b x2)
                         (set! x2 (+ a (/ (- b a) mphi)))
                         (set! x1 (- b (/ (- b a) mphi)))
                         (try a b x1 (fun x1) x2 (fun x2))
                )
                (else    (set! a x1)
                         (set! x1 (- b (/ (- b a) mphi)))
                         (set! x2 (+ a (/ (- b a) mphi)))
                         (try a b x1 (fun x1) x2 (fun x2))
                )
          )
       )
 )
)

(define xmin 0)
(set! xmin(golden-section-search a b))
  (display"interval=\t[")
  (display a)
  (display" , ")
  (display b)
  (display"]\n")
  (display"xmin=\t\t")
xmin
  (display"f(xmin)=\t")
(fun xmin)
