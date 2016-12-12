con <- file("output.log")
sink(con, append=TRUE)
sink(con, append=TRUE, type="message")

install.packages("../packages/foreach_1.4.3.tar.gz", repos=NULL, type="source")
install.packages("../packages/iterators_1.0.8.tar.gz", repos=NULL, type="source")
install.packages("../packages/doParallel_1.0.10.tar.gz", repos=NULL, type="source")
install.packages("../packages/neuralnet_1.32.tar.gz", repos=NULL, type="source")

setwd("~/cs344/term-project")
set.seed(1234567890)

library("foreach")
library("iterators")
library("doParallel")
library("grid")
library("MASS")
library("neuralnet")

cl <- makeCluster(detectCores())
registerDoParallel(cl)

trainset <- read.csv(file="~/cs344/term-project/csv/training-big.csv")
testset <- read.csv(file="~/cs344/term-project/csv/testing-big.csv")

classnet <- neuralnet(CLASS.10+CLASS.9+CLASS.8+CLASS.7+CLASS.6+CLASS.5+CLASS.4+CLASS.3+CLASS.2+CLASS.1 ~ S1.4+S1.3+S1.2+S1.1+C1.13+C1.12+C1.11+C1.10+C1.9+C1.8+C1.7+C1.6+C1.5+C1.4+C1.3+C1.2+C1.1+S2.4+S2.3+S2.2+S2.1+C2.13+C2.12+C2.11+C2.10+C2.9+C2.8+C2.7+C2.6+C2.5+C2.4+C2.3+C2.2+C2.1+S3.4+S3.3+S3.2+S3.1+C3.13+C3.12+C3.11+C3.10+C3.9+C3.8+C3.7+C3.6+C3.5+C3.4+C3.3+C3.2+C3.1+S4.4+S4.3+S4.2+S4.1+C4.13+C4.12+C4.11+C4.10+C4.9+C4.8+C4.7+C4.6+C4.5+C4.4+C4.3+C4.2+C4.1+S5.4+S5.3+S5.2+S5.1+C5.13+C5.12+C5.11+C5.10+C5.9+C5.8+C5.7+C5.6+C5.5+C5.4+C5.3+C5.2+C5.1, trainset, hidden = 47, lifesign = "full", threshold = 0.1, stepmax=1e7)

png(filename = "nnet.png")
plot(classnet, rep = "best")
dev.off()

temp_test <- subset(testset, select = c("S1.4","S1.3","S1.2","S1.1","C1.13","C1.12","C1.11","C1.10","C1.9","C1.8","C1.7","C1.6","C1.5","C1.4","C1.3","C1.2","C1.1","S2.4","S2.3","S2.2","S2.1","C2.13","C2.12","C2.11","C2.10","C2.9","C2.8","C2.7","C2.6","C2.5","C2.4","C2.3","C2.2","C2.1","S3.4","S3.3","S3.2","S3.1","C3.13","C3.12","C3.11","C3.10","C3.9","C3.8","C3.7","C3.6","C3.5","C3.4","C3.3","C3.2","C3.1","S4.4","S4.3","S4.2","S4.1","C4.13","C4.12","C4.11","C4.10","C4.9","C4.8","C4.7","C4.6","C4.5","C4.4","C4.3","C4.2","C4.1","S5.4","S5.3","S5.2","S5.1","C5.13","C5.12","C5.11","C5.10","C5.9","C5.8","C5.7","C5.6","C5.5","C5.4","C5.3","C5.2","C5.1"))
classnet.results <- compute(classnet, temp_test)

results <- data.frame(actual10= testset$CLASS.10, actual9 = testset$CLASS.9, actual8 = testset$CLASS.8, actual7 = testset$CLASS.7, actual6 = testset$CLASS.6, actual5 = testset$CLASS.5, actual4 = testset$CLASS.4, actual3 = testset$CLASS.3, actual2 = testset$CLASS.2, actual1 = testset$CLASS.1,prediction = classnet.results$net.result)
results$prediction.10 <- round(results$prediction.10)
results$prediction.9 <- round(results$prediction.9)
results$prediction.8 <- round(results$prediction.8)
results$prediction.7 <- round(results$prediction.7)
results$prediction.6 <- round(results$prediction.6)
results$prediction.5 <- round(results$prediction.5)
results$prediction.4 <- round(results$prediction.4)
results$prediction.3 <- round(results$prediction.3)
results$prediction.2 <- round(results$prediction.2)
results$prediction.1 <- round(results$prediction.1)

write.csv(results, "~/cs344/term-project/csv/results/results-big.csv")

stopCluster(cl)

sink()
sink(type="message")
