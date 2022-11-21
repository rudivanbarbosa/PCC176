
VNS <- c(1291621,1276812,1074541,826247, 220690, 216462, 187386, 141930 )
GRASP <- c(1112776,1041791,936556,777209,198891,181653,161913,133477)

t.test( VNS , GRASP , paired =TRUE , alternative ="greater")


VNSbloco1 <- c(1291621 , 1276812 , 1074541 , 826247)
shapiro.test ( VNSbloco1 )

VNSbloco2 <- c(220690 , 216462 , 187386, 141930)
shapiro.test ( VNSbloco2 )

GRASPbloco1 <- c(1159285 , 1094104 , 958631 , 798481)
shapiro.test ( GRASPbloco1 )

GRASPbloco2 <- c(210997 , 188222 , 171204, 138465)
shapiro.test ( GRASPbloco2 )

