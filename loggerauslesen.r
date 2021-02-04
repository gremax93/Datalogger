setwd("C:/Users/MaxGregoire/Documents/Uni/Hiwi/loggerdateienl1/ZA1/")
library(plyr)
install.packages("matrixStats")

library(matrixStats)

install.packages("plyr")
library(tidyverse)
file_list <- list.files()
dataset <- ldply(file_list, read.table, header=F, sep=";")
wasserstandpegellatte <-67.5
messwertlogger <- 215
logger_sohle <- wasserstandpegellatte+messwertlogger
dataset$datum <- as.POSIXct(dataset$V1, format="%Y-%m-%d %H:%M:%S")
dataset[,2:11] <- sapply(dataset[,2:11],as.numeric)
dataset$Median <- rowMedians(as.matrix(dataset[,2:11]))
dataset$waterhight <- logger_sohle-dataset$Median
dreisam <- table11012021144925874
dreisam$datum <- table11012021144925874[5]
plot( dataset$datum,dataset$waterhight,type="l",  ylab="Wasserstandshoehe [cm]", xlab="Datum")
ggplot(dataset, aes(datum, waterhight)) +
  geom_line()+
  theme_bw()+
  ggtitle("Pegel Logger D1")+
  xlab("Datum")+
  ylab("Wasserhoehe [cm]")

