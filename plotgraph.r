el = read.csv(file = 'adjacency.csv',header=FALSE,sep=',')
library(igraph)
library(ggplot2)
net <- as.matrix(el)
graph <- graph_from_adjacency_matrix(net)

V(graph)$color <- "gray50"
V(graph)$shape <- "circle"
E(graph)$width <- 6/sqrt(length(E(graph)))

E(graph)$color <- "orange"
E(graph)$arrow.size <- 0
V(graph)$size <- 100 / sqrt(length(V(graph)))

graph.degrees <- degree(graph)

graph.degree.histogram <- as.data.frame(table(graph.degrees))
graph.degree.histogram[,1] <- as.numeric(graph.degree.histogram[,1])

set.seed(123)
plot(graph,vertex.label=NA)
ggplot(graph.degree.histogram, aes(x = graph.degrees, y = Freq)) +
  geom_point() +
  scale_x_continuous("Degree",
                     breaks = c(2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192),
                     trans = "log2") +
  scale_y_continuous("Frequency",
                     breaks = c(2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192),
                     trans = "log2") +
  ggtitle("Degree Distribution (log-log)") +
theme_bw()


pdf('graph.pdf')
set.seed(123)
plot(graph,vertex.label=NA)
dev.off()

jpeg('graph.jpg')
set.seed(123)
plot(graph,vertex.label=NA)
dev.off()

jpeg('degree_distribution.jpg')
ggplot(graph.degree.histogram, aes(x = graph.degrees, y = Freq)) +
  geom_point() +
  scale_x_continuous("Degree\n(nodes with this amount of connections)",
                     breaks = c(0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024),
                     trans = "log2") +
  scale_y_continuous("Frequency\n(how many of them)",
                     breaks = c(0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024),
                     trans = "log2") +
  ggtitle("Degree Distribution (log-log)") +
theme_bw()
dev.off()

pdf('degree_distribution.pdf')
ggplot(graph.degree.histogram, aes(x = graph.degrees, y = Freq)) +
  geom_point() +
  scale_x_continuous("Degree\n(nodes with this amount of connections)",
                     breaks = c(2, 4, 8, 16, 32, 64, 128, 256, 512, 1024),
                     trans = "log2") +
  scale_y_continuous("Frequency\n(how many of them)",
                     breaks = c(2, 4, 8, 16, 32, 64, 128, 256, 512, 1024),
                     trans = "log2") +
  ggtitle("Degree Distribution (log-log)") +
theme_bw()
dev.off()
