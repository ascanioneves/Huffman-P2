graf <- read.delim(file.choose())

graf<-read.table(file.choose(), header = TRUE, sep = " ")
plot(graf$abb~graf$value, type='l',main="ABB X AVL", xlab="Valores", ylab="Comparações", col="blue")
lines(graf$avl~graf$value, type='l', col='red')




