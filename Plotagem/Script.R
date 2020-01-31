graf <- read.delim(file.choose())

graf<-read.table(file.choose(), header = TRUE, sep = " ")
plot(graf$abb~graf$value, main="ABB X AVL", xlab="Valores", ylab="Comparações", col="blue")
points(graf$avl~graf$value, col="red")




