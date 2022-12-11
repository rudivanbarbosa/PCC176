
VNS <- c(1291621,1276812,1074541,826247, 220690, 216462, 187386, 141930 )
GRASP <- c(1265078,1209529,1046721,818239,212086,201871,181800,139851)

t.test( VNS , GRASP , paired =TRUE , alternative ="greater")

VNSbloco1 <- c(1291621 , 1276812 , 1074541 , 826247)
shapiro.test ( VNSbloco1 )

VNSbloco2 <- c(220690 , 216462 , 187386, 141930)
shapiro.test ( VNSbloco2 )

GRASPbloco1 <- c(1265078,1209529,1046721,818239)
shapiro.test ( GRASPbloco1 )

GRASPbloco2 <- c(212086,201871,181800,139851)
shapiro.test ( GRASPbloco2 )
