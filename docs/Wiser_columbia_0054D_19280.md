Automated Model Reduction of Atmospheric Chemical Mechanisms

## Forwood Cloud Wiser IV

Submitted in partial fulfillment of the requirements for the degree of Doctor of Philosophy under the Executive Committee of the Graduate School of Arts and Sciences

## COLUMBIA UNIVERSITY

2025

© 2025

Forwood Cloud Wiser IV

All Rights Reserved

# **Abstract**

Automated Model Reduction of Atmospheric Chemical Mechanisms

## Forwood Cloud Wiser IV

The atmospheric chemistry of volatile organic compounds (VOC) has a major influence on atmospheric pollutants and particle formation. Accurate modeling of this chemistry is essential for air quality models. Complete representations of VOC oxidation chemistry are far too large for spatiotemporal simulations of the atmosphere, necessitating reduced mechanisms. This work details several new graph theory-based methods for mechanism reduction, optimization, and evaluation. Our newest algorithm, the Automated MOdel REduction 2.0 (AMORE 2.0), efficiently and accurately reduces VOC oxidation mechanisms to a desired size by removing, merging, and rerouting sections of the graph representation of the mechanism. This algorithm can reduce large mechanisms by over 90%, making them usable in atmospheric simulations. This work will improve our ability to accurately model the atmosphere, thereby supporting air quality management and advancing atmospheric chemical science.

# **Table of Contents**

|Acknow|ledgments**. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . **|**. . . . . . .** xiv|
|---|---|---|
|Dedicat|ion **. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . **|**. . . . . . .** xvi|
|Chapter|1:<br>Introduction and Background **. . . . . . . . . . . . . . . . . . . . **|**. . . . . . .**<br>1|
|1.1|Background . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . . .<br>2|
|1.2|Project Overview . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . . .<br>4|
|Chapter|2:<br>AMORE v1.0 Isoprene Mechanism **. . . . . . . . . . . . . . . . . **|**. . . . . . .**<br>13|
|2.1|Methods . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . . .<br>14|
||2.1.1<br>Full Mechanism Input . . . . . . . . . . . . . . . . . . . . . .|. . . . . . .<br>14|
||2.1.2<br>Priority Species . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . . .<br>15|
||2.1.3<br>Reduction Algorithm Development . . . . . . . . . . . . . . .|. . . . . . .<br>16|
||2.1.4<br>Manual Mechanism Optimization and Evaluation . . . . . . .|. . . . . . .<br>26|
|2.2|Results and Discussion . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . . .<br>38|
||2.2.1<br>Ambient Box Model Simulations . . . . . . . . . . . . . . . .|. . . . . . .<br>38|
||2.2.2<br>Chamber Box Model Simulations<br>. . . . . . . . . . . . . . .|. . . . . . .<br>44|
||2.2.3<br>CMAQ Testing . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . . .<br>46|
|Chapter|3:<br>AMORE 2.0 **. . . . . . . . . . . . . . . . . . . . . . . . . . . . . **|**. . . . . . .**<br>50|



i

|3.1|Introduction . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>50|
|---|---|---|
|3.2|Results . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>53|
|3.3|Discussion . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>60|
|3.4|Methods . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>62|
||3.4.1<br>Algorithm Description<br>. . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>62|
||3.4.2<br>Error Metric . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>70|
|Chapter|4:<br>Rapid Yield Algorithm**. . . . . . . . . . . . . . . . . . . . . . . . . **|**. . . . . .**<br>73|
|4.1|Mechanisms as Graphs . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>74|
|4.2|Rapid Yield Algorithm<br>. . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>77|
|4.3|Time-Dependent Yields . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>81|
|4.4|Asynchronous Reactants<br>. . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>86|
|4.5|Applications . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>89|
|Chapter|5:<br>Error Metrics **. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . **|**. . . . . .**<br>91|
||5.0.1<br>Basic Error Metric<br>. . . . . . . . . . . . . . . . . . . . . . . .|. . . . . .<br>92|
||5.0.2<br>Mechanism Assessment with Internal Measurements . . . . . .|. . . . . .<br>96|
||5.0.3<br>Mechanism Assessment with External Measurements . . . . . .|. . . . . . 106|
|Chapter|6:<br>Particle Swarm Optimization for Reduced Mechanisms<br>**. . . . . . . **|**. . . . . .** 111|
|6.1|Introduction . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . . 111|
|6.2|Background . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . . 113|
||6.2.1<br>Particle Swarm Optimization . . . . . . . . . . . . . . . . . . .|. . . . . . 113|
|6.3|Methods . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|. . . . . . 114|



ii

||6.3.1|Particle Swarm Optimization . . . . . . . . . . . . . . . . . . . . . . . . .|116|
|---|---|---|---|
||6.3.2|Objective Function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|117|
|6.4|Result|s and Discussion . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|122|
|6.5|Concl|usion<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|131|
|Chapter|7:<br>Art|ifcially Intelligent Mechanism Reduction for Gas-phase Isoprene Oxidation|137|
|7.1|Introd|uction . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|137|
|7.2|Metho|ds . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|138|
||7.2.1|Genetic Algorithm (GA) . . . . . . . . . . . . . . . . . . . . . . . . . . .|139|
||7.2.2|Fitness function . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|141|
||7.2.3|Domain knowledge inclusion into GA . . . . . . . . . . . . . . . . . . . .|146|
||7.2.4|Parameter Optimization . . . . . . . . . . . . . . . . . . . . . . . . . . . .|150|
|7.3|Result|s and Discussion . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|150|
|7.4|Concl|usions and Future Work . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|156|
|7.5|Additi|onal Tables . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|156|
|Chapter|8:<br>Gr|aph Theory Assisted Gradient Descent Optimization of Reduced Mechanisms|161|
|8.1|Introd|uction . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|161|
|8.2|Metho|ds . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|162|
||8.2.1|Mechanism Evaluation and Data Preparation<br>. . . . . . . . . . . . . . . .|162|
||8.2.2|Gradient Descent . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|165|
|8.3|Result|s . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|170|
|8.4|Discus|sion . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|175|



iii

Chapter 9: Clustering Algorithms for AMORE 2.0 Input Optimization **. . . . . . . . . . .** 176 Chapter 10: Conclusions and Future Work **. . . . . . . . . . . . . . . . . . . . . . . . . . .** 183 References **. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .** 187

iv

# **List of Figures**

- 1.1 Overview of the topics for this thesis and their relevant chapters in parenthesis. . . 5

- 1.2 Schematic diagram of the AMORE 2.0 algorithm. Gray indicates mechanisms, green indicates mechanism analysis steps, red indicates mechanism reduction steps, purple indicates mechanism optimization steps, and blue indicates supplemental algorithms or methods to the AMORE 2.0 algorithm. . . . . . . . . . . . . . . . . 8

- 2.1 Schematic of the AMORE algorithm. The sub-algorithms are shown in order of implementation. Brackets are used to specify a pathway within the mechanism, with each oxidant or nitrogen oxide within the brackets representing a reaction in a sequence involving that oxidant. For example, the pathway {OH, NO} represents a sequence of two reactions joined by an intermediate, in which OH and NO are reactants in the two reactions. The pathway {OH, NO} is shown as an example for sub-algorithms 2-4. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 18

- 2.2 The original AMORE algorithmically generated mechanism prior to manual adjustment (left) and the final AMORE-Isoprene mechanism (right). Changes are highlighted in blue. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 30

- 2.3 Box model simulations (T = 292 K, p = 1000 hPa) showing the improvement in performance of the AMORE mechanism for HO2 and NO _𝑥_ after adding these species to the products of reactions 4 (b) and 5 (a). The original and updated reactions are shown above the plots. Inputs are a) 200 ppb H2O2, 1 pbb NO, 10 ppb isoprene, and moderate photolysis conditions (F0AM photolysis parameter = 1). b) 200 ppb H2O2, 1 pbb NO, 10 ppb isoprene, and high photolysis conditions (F0AM photolysis parameter = 3.5). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 35

- 2.4 Box model predictions of HO2 from multiple mechanisms (292 K and 1000 hPa) for the following conditions: a) Low NO _𝑥_ b) High NO _𝑥_ c) High O3 d) High NO3 e) High NO3, low hv, and f) [61] Chamber. . . . . . . . . . . . . . . . . . . . . . . 39

- 2.5 Box model predictions of formaldehyde from multiple mechanisms (292 K and 1000 hPa) for the following conditions: a) Low NO _𝑥_ b) High NO _𝑥_ c) High O3 d) High NO3 e) High NO3, low hv, and f) [61] Chamber. . . . . . . . . . . . . . . . 40

v

- 2.6 Box model predictions of the hydroxyl radical from multiple mechanisms (292 K and 1000 hPa) for the following conditions: a) Low NO _𝑥_ b) High NO _𝑥_ c) High O3 d) High NO3 e) High NO3, low hv, and f) [61] Chamber. . . . . . . . . . . . . . . 42

- 2.7 Measured error (Equation 4) of AMORE-Isoprene mechanism under six different conditions for seven select species groups. Errors are averaged between species for multiple-species groups. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 43

- 2.8 IEPOX concentration comparison between chamber data from [61] and F0AM box model simulations using the reported chamber conditions. The Caltech full mechanism closely matches the measured values, as does the AMORE-Isoprene mechanism. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 45

- 2.9 Binned mean bias of AMORE-Isoprene and baseline CRACMM for (a) formaldehyde and (b) ozone compared to AQS data for the Northeast U.S. during summer 2018. Numbers for boxplots indicate the number of data points in each observed range. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 46

- 3.1 Comparison of the full isoprene mechanism graph and an AMORE 2.0 reduced mechanism (15 species) graph for a subset of the mechanism. These graphs show isoprene oxidation via the hydroxyl radical over the first three generations. . . . . . 53

- 3.2 Mechanism error (Equation 8.4) plotted against number of species for several AMORE 2.0 isoprene mechanisms. Error is calculated using equation 8.4 and the Caltech full isoprene mechanism as a reference, and species weightings listed out in section 3.4.2. Three existing reduced isoprene mechanisms are shown as a benchmark: the Caltech reduced plus mechanism (121 species), the Caltech mini isoprene mechanism (92 species), and the AMORE 1.2 mechanism (12 species). Similar sized AMORE mechanisms are highlighted in purple. . . . . . . . . . . . . . . . . . . . 54

- 3.3 Bias (mol/mol isoprene) of the most important species in the isoprene system for 1,000 GEOS-Chem derived atmospheric conditions. Outliers are omitted for visual clarity, the full dataset is available in the supporting files. a) AMORE 2.0 109 sp (109 species, 330 reactions) compared to Caltech reduced plus mechanism (121 species and 379 reactions) b) AMORE 2.0 74 sp (74 species, 238 reactions) compared to Caltech mini mechanism (91 species and 266 reactions) c) AMORE 2.0 15sp (15 species, 61 reactions) compared to AMORE 1.2 mechanism (12 species and 22 reactions). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 56

- 3.4 Categories of all SOA-producing camphene species shown divided by color plotted on a Log10[Vapor Pressure (Pa)] vs. Log10[Henry’s Law Constant (M/atm)] axis. . 58

vi

|3.5|Comparison of SOA concentration for three AMORE Reductions (177 species and<br>1220 reactions, 30 species and 183 reactions, 6 species and 18 reactions) of the<br>GECKO camphene mechanism (103,694 species, 775,070 reactions) under three<br>different GECKO box model run conditions.<br>. . . . . . . . . . . . . . . . . . . .|59|
|---|---|---|
|4.1|Simple mechanisms and their graph representation. . . . . . . . . . . . . . . . . .|75|
|4.2|Simple mechanisms with their graph representation and yields of all species listed<br>above each species. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|78|
|4.3|Comparison of the Rapid Yield Algorithm to a box model for all species in the<br>isoprene mechanism under six different conditions.<br>. . . . . . . . . . . . . . . . .|82|
|4.4|Comparison of the time-dependent Algorithm and the F0AM box model for formalde-<br>hyde (a,d,g), trans-IEPOX (b,e,h), and HMML (c,f,i) under the high OH (a,b,c),<br>high OH and NO (d,e,f), and high NO3low hv (g,h,i) conditions from Table 5.0.2,<br>with the isoprene concentration set to 1 pbb for each condition. . . . . . . . . . . .|85|
|4.5|Toy model mechanism for the prediction of end products D and F given asyn-<br>chronous reactants B and E. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|87|
|4.6|The ratio of end time concentrations of species _𝐹_and species _𝐷_versus log10(_𝑘_1)<br>from the toy model mechanism in Figure 4.5. Box model measured values shown<br>as individual data points compared to the predicted values given by Equation 4.12<br>(red line). In this run,_𝑘_3=1_𝑠_<sup>−1</sup>,_𝑘_2=5∗10<sup>−8</sup>_𝑀_<sup>−1</sup>_𝑠_<sup>−1</sup>,[_𝐴_]0 =1ppb,_𝛼_1 =0_._0276,<br>and_𝛼_2 =0_._1.<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|89|
|5.1|The Error Metric (_𝐸_) used throughout this work given in Equation 5.2 as a function<br>of the test value_𝑇_(log scale) with a reference value_𝑅_=1. . . . . . . . . . . . . .|94|
|5.2|The Error Metric (_𝐸_2) given in Equation 5.4 as a function of the test value_𝑇_(log<br>scale) with a reference value_𝑅_=1. . . . . . . . . . . . . . . . . . . . . . . . . . .|95|
|5.3|Visual comparison of metric_𝐸_<sup>_𝑑_</sup><br>_𝑠_<sup>for species</sup><sup>_𝑠_for two different different test mecha-</sup><br>nisms_𝑇_1(blue shaded area) and_𝑇_2(red shaded area) compared to reference mech-<br>anism R. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|99|
|5.4|Visual comparison of metric_𝐸_<sup>_𝑑_</sup><br>_𝑝𝑠_<sup>for production</sup> <sup>_𝑝_(</sup><sup>_𝑡_) of species</sup><sup>_𝑠_for two different</sup><br>different test mechanisms_𝑇_1(blue shaded area) and_𝑇_2(red shaded area) compared<br>to reference mechanism R.<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|101|



vii

- 5.5 Comparison of formaldehyde production in a diurnal cycle (left) and constant high OH (right) for two versions of the AMORE v1 Isoprene mechanism with the full isoprene mechanism for reference. . . . . . . . . . . . . . . . . . . . . . . . . . . 109

- 6.1 The change in optimization variables – here, stoichiometric coefficients – as PSO proceeds from one iteration to the next. The red-colored boxes in the updated mechanism on the right depict the stoichiometric coefficients with changed values. The node attributes such as _OH_ , _𝑂_ 3, and others refer to the type of reaction, which remains unchanged throughout the optimization. . . . . . . . . . . . . . . . . . . . 118

- 6.2 Best objective function score within the population plotted against the number of different parameter sets tested. Plots shown for multiple PSO runs on the AMORE v1.2 mechanism with varying particle populations of 5, 25, 50, and 100. . . . . . . 123

- 6.3 Example concentration plots of the reference mechanism, AMORE v1.1 mechanism, and AMORE v1.1 50×100 PSO-optimized mechanism without rate constant optimization, run for a particle population of 50, and 100 generations. The measured fitness values for AMORE v1.1 are: HCHO, 0.17; IEPOX, 0.32; ISOPN, 0.2; MGLY, 0.66; MACR, 0.02; GLY, 0.38. The measured fitness values for AMORE v1.1 50×100 PSO are: HCHO, 0.04; IEPOX, 0.00; ISOPN, 0.38; MGLY, 0.02; MACR, 0.01; GLY, 0.01. The run input condition is the high OH test condition from Table 8.2.1. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 127

- 6.4 Example concentration plots of the reference mechanism, AMORE v1.2 mechanism, and AMORE v1.2 50×100 PSO-optimized mechanism without rate constant optimization, run for a particle population of 50, and 100 generations. The measured fitness values for AMORE v1.2 are: HCHO, 0.02; IEPOX, 0.08; ISOPN, 0.47; MGLY, 0.40; MACR, 0.29; GLY, 0.08. The measured fitness values for AMORE v1.2 50×100 PSO are: HCHO, 0.19; IEPOX, 0.01; ISOPN, 0.45; MGLY, 0.02; MACR, 0.02; GLY, 0.16. The run input condition is the high OH test condition from Table 8.2.1. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 132

- 6.5 Bias (ppb) from reference value for the optimized AMORE v1.1 mechanism for 6 different conditions (Table 8.2.1), and the 6 species – _𝑂𝐻_ , _𝐻𝑂_ 2, _𝑁𝑂_ , _𝑁𝑂_ 2, _𝐻𝐶𝐻𝑂_ , and _𝐼𝐸𝑃𝑂𝑋_ . There is considerable decline in the bias for the optimized mechanisms (blue and green), when compared to manually edited AMORE v1.1 mechanism (red). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 133

- 6.6 Bias from reference value for the optimized AMORE v1.2 mechanism for 6 different conditions (Table 8.2.1, and the 6 species – _𝑂𝐻_ , _𝐻𝑂_ 2, _𝑁𝑂_ , _𝑁𝑂_ 2, _𝐻𝐶𝐻𝑂_ , and _𝐼𝐸𝑃𝑂𝑋_ . There is considerable decline in the bias for the optimized mechanisms (blue and green), when compared to manually edited AMORE v1.2 mechanism (red).134

viii

- 7.1 GA-AMORE algorithm. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 140 7.2 Two example mechanisms, one with part of the chemistry disconnected from isoprene (a), and one in which all of the chemistry is connected to isoprene (b). . . . . 147

|7.3|Genetic operators used in GA-AMORE: (a) selection; (b) new reaction; (c) replace<br>products; (d) new mechanism. The candidate reduced mechanisms highlighted<br>here are only meant for illustrative purposes, on how the genetic operators act on<br>them, as the population updates from generation 29 to generation 30. . . . . . . . . 148|
|---|---|
|7.4|Best individual score within the population versus the number of generations in the<br>Genetic Algorithm mechanism search. . . . . . . . . . . . . . . . . . . . . . . . . 151|
|7.5|Comparison of bias in net yield of a select set of key isoprene derived species<br>between the best GA-AMORE isoprene mechanism (orange) and the AMORE v1.2<br>isoprene mechanism (blue). . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 153|
|7.6|Box model output concentration plots are shown for three key organic VOC species:<br>formaldehyde (HCHO), isoprene epoxydiol (IEPOX), and methacrolein (MACR)<br>and three input conditions (high OH, high O3, and high NO3). The GA-AMORE<br>mechanism is compared to the full isoprene mechanism and the AMORE v1.2<br>mechanism. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 154|
|7.7|Graph representations of the best performing GA-AMORE mechanism (b) and the<br>AMORE v1.2 mechanism (a), with two other with GA-AMORE mechanisms (c,d)<br>shown as well. End products represented as Out. The nodes represent species,<br>and the edges represent reactant product pairs within the mechanism. Edge labels<br>represent the background reactant involved in the reaction. Red indicates edges<br>with more signifcant reaction rates.<br>. . . . . . . . . . . . . . . . . . . . . . . . . 157|
|7.8|Comparison of bias in net yield of a select set of key isoprene derived species<br>between two additional well-forming GA-AMORE isoprene mechanisms (orange<br>in a and b) and the AMORE v1.2 isoprene mechanism (blue). . . . . . . . . . . . . 159|
|8.1|Sample isoprene mechanism. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 164|
|8.2|Bipartite graph example where top nodes represent coeffcients and bottom nodes<br>represent yields. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 167|
|8.3|Example of undirected graph sorting on a bipartite graph where the top nodes rep-<br>resent coeffcients and the bottom nodes represent yields. . . . . . . . . . . . . . . 168|



ix

- 8.4 Box model results of various mechanisms. Purple: previously published reduced mechanisms; blue: unoptimized AMORE reduced mechanisms; green: optimized AMORE reduced mechanisms. . . . . . . . . . . . . . . . . . . . . . . . . . . . . 172

- 8.5 Box model plots for various species comparing the full mechanism, the reduced mechanism, and optimized reduced mechanism at high OH, low NO _𝑥_ conditions. . 173

- 9.1 Error vs. number of clusters for the four different clustering methods tested for this work. Lower error signifies more robust clusters. . . . . . . . . . . . . . . . . . . 180

- 9.2 Concentration values of NO, HO2 and OH for selected input conditions using the four different clustering methods: Spectral clustering on yields of gridded data (S GY), k-means clustering on yields of atmospheric data (K-M UY), k-means clustering on yields of gridded data, and k-means clustering on atmospheric data (K-M U). All methods selected four clusters, and the cluster performance is shown by the color of the data. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 181

x

# **List of Tables**

|2.1|Sizes of select isoprene mechanisms including the mechanism in this work. Larger<br>mechanism sizes are self-reported. For smaller mechanisms, species and reactions<br>were recounted for this work using the following criteria: i) only species unique<br>to isoprene chemistry are included, which excludes species that do not contain the<br>isoprene carbon backbone ii) All reactions involving species unique to isoprene are<br>counted iii) Heterogeneous reactions involving isoprene species are not counted.<br>|.<br>13|
|---|---|---|
|2.2|Baseline and elevated values of input parameters used in the pathway importance<br>algorithm, a component of the AMORE algorithm.<br>. . . . . . . . . . . . . . . .|.<br>22|
|2.3|F0AM box model testing input conditions used for calculating the error metric<br>and evaluating the AMORE-Isoprene mechanism. Bolded values represent species<br>concentrations that were held constant. All other concentrations varied with time<br>after initiation of the simulation.<br>. . . . . . . . . . . . . . . . . . . . . . . . . .|.<br>28|
|2.4|The AMORE-Isoprene mechanism reactions and rate constants. Mechanism spe-<br>cifc species are listed in the text. . . . . . . . . . . . . . . . . . . . . . . . . . .|.<br>32|
|2.5|Species used in the calculation of the mechanism error metric and their correspond-<br>ing weight. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .|.<br>37|
|2.6|Total Error (individual species error described in Equation 4, species weighting<br>shown in Table 2.5, further discussion in Section 5.2) and mechanism size for four<br>reduced isoprene mechanisms with the Caltech full mechanism as a basis of com-<br>parison. Individual species error shown averaged over the six tested conditions.<br>.|.<br>44|
|3.1|Six different run conditions used to evaluate mechanisms. All species values have<br>units of ppb. Photolysis is a unitless constant.<br>. . . . . . . . . . . . . . . . . . .|.<br>72|
|5.1|Six different run conditions used to evaluate mechanisms. All species values have<br>units of ppb. Photolysis is a unitless constant.<br>. . . . . . . . . . . . . . . . . . .|. 105|



xi

|5.2|The range of conditions for key atmospheric species and parameters for the GEOS-<br>Chem data set. All atmospheric species are in units of parts per billion (ppb) and<br>Sun is a unitless measure of the solar intensity relative to the maximum intensity<br>of 1. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 106|
|---|---|
|6.1|Six different run conditions used to evaluate mechanisms. All species values have<br>units of ppb. Photolysis is a unitless constant.<br>. . . . . . . . . . . . . . . . . . . . 120|
|6.2|Table showing measured ftness values for six reduced isoprene mechanisms under<br>six different testing conditions. . . . . . . . . . . . . . . . . . . . . . . . . . . . . 126|
|6.3|Table showing mean and standard deviation of measured ftness values for six re-<br>duced isoprene mechanisms under 1000 different testing conditions derived from<br>a global GEOS-Chem simulation. . . . . . . . . . . . . . . . . . . . . . . . . . . . 126|
|7.1|The different reaction types and reaction rates, along with the frst and second<br>reactant. These were specifed as the rules on the basis of which the reactions<br>were created by GA-AMORE in a candidate reduced mechanism. SUN refers to a<br>unitless numerical value between 0 to 1 assigned to the strength of the sun’s radiation.158|
|7.2|Conditions used for the genetic algorithm to create reduced mechanism structures.<br>All species values are in units of ppb and photolysis is a unitless constant describing<br>the rate of photolytic reactions. . . . . . . . . . . . . . . . . . . . . . . . . . . . . 159|
|7.3|Six different run conditions used to evaluate mechanisms in the Particle Swarm<br>Optimization. All species values have units of ppb. Photolysis is a unitless constant. 160|
|8.1|Six different run conditions used to evaluate mechanisms. All species values have<br>units of ppb. Photolysis is a unitless constant.<br>. . . . . . . . . . . . . . . . . . . . 162|
|8.2|Performance of various methods along with the time in hours that each method<br>took. Particle swarm optimization is the fastest method but least effective. Anti-<br>community clustering and standard gradient descent are equally effective, but anti-<br>community clustering takes a quarter of the time.<br>. . . . . . . . . . . . . . . . . . 171|
|8.3|Errors for a set of priority species for a 12 species AMORE 2.0 isoprene mech-<br>anism after several different methods of optimization, including Standard Gradi-<br>ent Descent (GD), Anti-Community Clustering (ACC), Undirected Graph Shorting<br>(UGS), and Randomly sorted coeffcients (RSC). The un-optimized mechanism is<br>shown for comparison.<br>. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 174|



xii

- 9.1 The range of conditions for key atmospheric species and parameters for the GEOSChem data set. All atmospheric species are in units of parts per billion (ppb) and Sun is a unitless measure of the solar intensity relative to the maximum intensity of 1. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 178

xiii

# **Acknowledgements**

I would like to begin by thanking everyone who has been involved with the development, research, and writing of this dissertation. This work would not have been possible without the support and contributions of many individuals.

First and foremost, I am deeply grateful for Professor Faye McNeill, whose support has been incredible. She has been an important mentor throughout my PhD. Her guidance, insightful feedback, and patience have been invaluable throughout this experience. Not only has she shaped the final product of this dissertation, but she has also played a crucial role in my personal and academic growth.

I would also like to thank Dr. Siddhartha Sen for his generosity in mentoring me and providing critical insights that significantly improved the direction of my research. Your support and expertise have been greatly appreciated.

Thank you to my current and former colleagues in the McNeil group: Han Huynh, Do Young Maeng, Katie Stevenson, Alexander Berman, Reese Carter, Julie Young, Nate Lui Mettke, Zifeng Tang, Miranda Hack, Sandhya Sethuraman, Farideh Hosseini Narouei, Sathish Swaminathan, Ryan Ward, and Kelly Rodriguez. It has been a pleasure working with such a dedicated team. I wish to acknowledge the support of Daniel Westervelt, Daven Henze, and Arlene Fiore for their work on the project proposal and coauthorship and contributions to Chapters 2 and 3. I would like to thank Havala Pye, Bryan Place, and Nash Skipper at the Environmental Protection Agency for their contributions and coauthorship of Chapter 2 and contributions to Chapter 5. I am deeply grateful to Zhizhao Wang, Julia Lee-Taylor, Kelley Barsanti, and John Orlando at the National

xiv

Center for Atmospheric Research for their contributions and coauthorship of Chapter 3. I am thankful for the invaluable support of Arijit Chakraborty and Professor Venkat Venkatasubramanian for their coauthorship and contributions to Chapters 6 and 7, Julie Young for her contribution to Chapter 4, Alexander Berman for his contribution and coauthorship of Chapter 8, Reese Carter for his contributions and coauthorship of Chapter 9, and Benjamin Yang for his contributions to Chapter 5. Thank you to Paul Allen for his editing help.

This research was generously supported by the EPA under Assistance Agreement No. 84001301 awarded. I am grateful for your funding and support that made this project possible.

Lastly, I would like to thank my family for your support in helping me complete this work. I couldn’t have done it without you all.

Mom and Dad: Your sacrifices and encouragement have been the foundation of everything I’ve accomplished. Your love and belief in me have allowed me to take risks and pursue my dreams. I cannot thank you enough for everything you’ve done.

Caroline: You are my best friend, my rock, and my greatest supporter. Completing a PhD while raising two children is no small feat, but your love and patience made it possible. I could not have done this without you. Also, thank you for your help with editing.

Brooks and Lily: You both are the joys of my life. Brooks, your boundless curiosity and love for the outdoors make every day brighter. Lily, your laughter is infectious and I can’t wait to watch you grow and learn. I can’t wait to celebrate my graduation with you both by my side.

Harriet: You are the best sister a brother could ask for. Your support and kindness have meant the world to me, and I’m lucky to have you in my life.

xv

# **Dedication**

To Brooks and Lily, who are my greatest joys and inspirations.

xvi

# **Chapter 1: Introduction and Background**

Atmospheric chemistry, which includes interactions between volatile organic compounds (VOC), atmospheric oxidants, and particulate matter, has far-reaching implications for human health and the climate. In particular, atmospheric chemistry has a significant impact on the concentration of gas-phase pollutants such as ozone and formaldehyde, and particulate matter, which is both hazardous to human health, and has a complex context-dependent impact on climate and weather via radiative forcing contributions [1]. Having a strong understanding of the sources and sinks of the atmospheric species is essential to predicting and understanding the atmosphere. Atmospheric chemical models are used to predict the concentrations of key species, identify natural and anthropogenic sources of pollutants (including some VOCs), and quantify the impact of existing and potential environmental policies. These models, while very detailed, are inherently limited by computational constraints and cannot account for the full complexity of the atmosphere.

In particular, the oxidation of atmospherically relevant VOCs, such as isoprene and camphene, is a particularly complex aspect of atmospheric chemistry due to the capacity of these compounds to acquire multiple functional groups at many sites, leading to a combinatorial explosion in species and reactions. Through oxidation, these species produce secondary organic aerosol (SOA) and toxic gas-phase products such as formaldehyde, and influence oxidant gas concentrations. Many extensive chemical mechanisms have been developed for VOC oxidation, but due to their large size, they are unusable in the chemical transport models [2, 3, 4] that are the state of the art for atmospheric chemistry models. Manual reduction has been a common approach in the past [5, 6, 7, 8, 9], but it is labor-intensive, prone to human error, and has reduced opportunities for optimization. While algorithmically generated reduced mechanisms have been developed in atmospheric chemistry [10, 11, 12, 13, 14], these methods lack the combination of versatility, computational efficiency, and accuracy after extensive reduction necessary to make algorithmic reduction more

1

widespread.

Our work has been focused on creating algorithms and ancillary tools for the development of reduced VOC oxidation mechanisms. The purpose of this is three-fold. First, it is desirable to reduce the labor needed to create reduced mechanisms, as this will minimize the barriers to developing new reduced mechanisms. Secondly, it is necessary to increase the computational efficiency of chemical mechanisms, and this can be achieved through mechanism reduction. Thirdly, it is necessary to improve the accuracy of reduced mechanisms, which can be done by systematically reducing larger, more accurate mechanisms. The ultimate goal of this work is to develop a set of tools which can be used to accurately and efficiently reduce large chemical mechanisms to a desired size for their eventual incorporation into atmospheric chemical models, thereby increasing the breadth and accuracy of these models while minimizing computational cost.

We have focused our efforts primarily on the isoprene mechanism, both because it the second most abundant VOC after methane [15] (which has negligible contribution to SOA), and because it is very well-studied, with recent, highly detailed mechanisms available for use. This chemistry is highly detailed and extensive, containing 400 species [16], so it is a useful test case for our methods. To generalize our approach, we have also worked with a much larger camphene mechanism, which was algorithmically generated [17]. In this Chapter, we discuss the motivations for this work, and outline the scope of the overall project.

## **1.1 Background**

Isoprene is the most abundant non-methane hydrocarbon in the atmosphere. It is emitted by a wide range of plants from their leaves as a response to heat stress and reactive oxidants in the air [18]. As a result, it is most abundant in warmer months. It has a major impact on tropospheric oxidant levels [19] and contributes to secondary organic aerosol (SOA) formation (and therefore fine particulate matter, PM2.5) in many parts of the U.S. and the world [20, 21, 22, 23, 24]. During the warm season, isoprene emissions enhance both regional and hemispheric ozone abundances at northern mid-latitudes [25, 26]. Isoprene oxidation chemistry contributes to natural background

2

ozone and particulate matter over much of the U.S. during the warm season [27]. Different representations of isoprene chemistry lead to uncertainty in air pollutant responses to anthropogenic emission reductions [28], and differences in model estimates of the background versus anthropogenic fractions [29, 27].

Knowledge of the isoprene oxidation reaction mechanism, including key pathways for both ozone and aerosol formation, has advanced rapidly over the last two decades [16]. The full chemical mechanism for isoprene oxidation, as it is currently understood, consists of several hundred species (up to 602 in MCM v3.3.1 [2]) and ∼1000 reactions. Due to its size and complexity, including every known intermediate species and reaction in the isoprene oxidation network in 3D air quality and atmospheric chemistry models is not feasible. Therefore, most models employ reduced isoprene mechanisms. For reduced mechanisms, there is a trade-off between mechanism size (i.e., the number of species and reactions represented) and accuracy. The goal is to find the smallest possible reduced mechanism that still provides the accuracy required for the modeling application. Commonly used reduced isoprene mechanisms range in size from ∼10 to ∼200 species. The reduced models, including the Common Representative Intermediates mechanism [6], Caltech Reduced Plus mechanism [30], Regional Atmospheric Chemistry mechanism [31], and Carbon Bond mechanism [32] have been developed manually by expert air quality scientists using techniques such as surrogate mechanisms (lumped structure [9] or lumped species [33, 31, 34]), and empirical parameterization, along with expert knowledge of the reaction system. While these approaches have been successful in representing atmospheric chemistry for the specific chemical and environmental scenarios for which they were developed, the resulting models tend to lack flexibility to be able to be adapted to new scenarios or to be rapidly updated. Their implementation is also labor intensive.

Camphene is an abundant monoterpene that is primarily found in wildfire smoke [35] where it contributes to SOA, but has been less studied [3, 17] than isoprene. Where abundant, Camphene produces formaldehyde and other small organic species and impacts the NO _𝑥_ and HO _𝑥_ budget. In contrast to the Caltech isoprene mechanism, the GECKO-A camphene mechanism was developed

3

algorithmically. The six-generation GECKO-A camphene mechanism contains 103,694 species and 775,070 reactions. The GECKO-A algorithm automatically generates VOC oxidation mechanisms, and utilizes available data and theoretical predictions of product branching ratios and rate constants [36]. Because it is automated, many more species can be included than would be feasible for a manually developed mechanism. As of now, there is no reduced camphene model that has been used in a chemical transport model, highlighting the need for mechanism reduction.

Automated chemical mechanism reduction techniques provide the opportunity to flexibly and rapidly generate accurate reduced chemical mechanisms, and lower the barrier to updating the mechanism as new knowledge becomes available. While automated mechanism reduction has been applied in limited studies in atmospheric chemistry [37, 38, 11, 39, 40, 41, 42, 43], it has been further developed in the field of combustion [44, 45, 46, 47, 48, 49, 50, 51]. Combustion mechanisms have a number of features in common with the isoprene oxidation mechanism, including their complexity and the large number of intermediates involved. Thus, techniques developed for the application to combustion mechanisms may be applicable to the isoprene oxidation mechanism as well.

The methods of model reduction, whether automated or manual, fall into two main categories. The first is reduction by removing less important species or reactions. The other method is to group species and reactions together which may participate in similar reaction pathways (chemical lumping). Each method aims to reduce the computational cost for simulating the mechanism by reducing the complexity and size of the reaction network, while retaining accuracy within a given tolerance.

## **1.2 Project Overview**

Automated mechanism reduction requires an initial candidate mechanism to reduce, a suitable algorithm for the accurate reduction of the mechanism, and a method of testing the performance of the reduction. Through the course of this project, we have added to and modified our candidate mechanisms, developed several methods of mechanism reduction, and developed a testing

4



<!-- Start of picture text -->
Mechanism Testing Mechanism Reduction Reduction Inputs<br>Rapid Yield Algorithm (4) Isoprene Mechanism<br>AMORE 1.0 (2)<br>Box Models (2,3,6,7,8,9)<br>AMORE 2.0 (3)<br>Chemical Transport  Camphene Mechanism (3)<br>GA-AMORE (7)<br>Models (5) Optimal Input Selection (9)<br>Particle Swarm<br>Error Measurement (5) Optimization (6)<br>Gradient Descent (8)<br>Mechanism Evaluation Mechanism Optimization<br><!-- End of picture text -->

Figure 1.1: Overview of the topics for this thesis and their relevant chapters in parenthesis.

framework for the assessment of reduced mechanisms. The biggest achievement of this project is the AMORE 2.0 algorithm, which is described in Chapter 3. This algorithm is an efficient and accurate method for the reduction of atmospheric oxidation mechanisms. It is the culmination of many years of testing and development, and we have demonstrated its accuracy for two candidate mechanisms: isoprene and camphene. Chapter 3 contains the final draft of the manuscript which has been submitted to be published and is available as a preprint [52]. In addition to this work, we have developed two other mechanism reduction methods, AMORE 1.0 (Chapter 2) [53] and GA-AMORE (Chapter 7) (available as a preprint [54]). To improve mechanism accuracy, we have developed two different optimization tools, AMORE PSO (Chapter 6) (soon to be available on a preprint server) and AMORE Gradient Descent (Chapter 8). We discuss a key sub-algorithm, the Rapid Yield Algorithm, in Chapter 4; our mechanism testing methods and error metrics in Chapter 5; and additional work on the optimization of inputs to the AMORE 2.0 algorithm in Chapter 9. Figure 1.1 shows the different topics within the AMORE project, their corresponding chapters, and how they relate to each other.

Our initial attempt at mechanism reduction followed the Directed Relational Graph method [49]. In this method, which was developed for combustion mechanisms, the mechanism is rep-

5

resented as a graph, with species becoming vertices, and edges forming between each reactantproduct pair for each reaction. These edges are assigned a weighting based on the relative contribution of the reaction to the production/loss of the species involved. Edges are then removed if their weighting is less than some threshold _𝜖_ . However, we quickly ran into issues with this approach. First, there was no method of ensuring that the mechanism remained a single connected set of reactions. For example, an edge might removed that connected two different parts of the mechanism, rendering them separated. This poses a problem for atmospheric oxidation mechanisms, where all species are derived from the source species. When the weighting threshold _𝜖_ for edge removal was small (<0.01), this effect was limited to less important parts of the mechanism, but to achieve the desired mechanism size, we had to have _𝜖>_ 0 _._ 01 which inherently removed higher importance pathways from the mechanism, eventually leaving an inaccurate final mechanism.

To maintain connectivity, we added a constraint that at least one pathway remain from the source species to each priority species. The resulting mechanisms still did not have very high accuracy, and the minimum reduced mechanism size from this constraint was still larger than desired, as many priority species were reached after several reactions generations, necessitating many intermediates. While this method was not effective for our use case, it provided several valuable lessons. We learned that the method did not have a way to condense multiple generations, and any chemistry that was removed remained completely unrepresented in the reduced mechanism. This could be overcome by rerouting over removed chemistry and skipping reaction generations. However, our biggest takeaway was the graph theoretical framework for mechanism representation. This framework has informed all of our subsequent work.

For our second attempt at mechanism reduction, we developed our own graph theory-based method which is described in Chapter 2. The Automated MOdel REduction (AMORE) 1.0 algorithm was developed and used to create the AMORE v1.0 isoprene mechanism [53]. This work was previously published in Geoscientific Model Development. In this method, the reduced mechanism was built from scratch, using the graph representation of the mechanism to identify the essential mechanistic pathways in the full mechanism, and using these pathways as the base structure of

6

the reduced mechanism. Products from these pathways were identified and manually optimized afterwards. Rate constants were chosen by the type of reaction involved and manually optimized as well. This method required significant manual input, but it was successful at creating a 12 species reduced isoprene mechanism that was effective in matching the behavior of the 400 species mechanism it was based off. We compared this mechanism to other reduced mechanisms in box models and the Community Multiscale Air Quality model (CMAQ), which is a chemical transport model. It performed well in both settings. This mechanism was subsequently updated and tested in GEOS-Chem [55] (another chemical transport model), and again in CMAQ [8, 56]. While we were successful in our goal of producing a reduced isoprene mechanism, there were some limitations to this method. The first limitation was that by building the mechanism from scratch, there was a practical limit on the maximum mechanism size, meaning that larger, more detailed reduced models would not be possible. Furthermore, it required significant manual optimization to be accurate, whereas the goal of this project was to minimize manual input. Because of these limitations, we began working on a new approach.

The AMORE 2.0 algorithm was developed to address the limitations of our prior work and to develop a method that could be easily and reliably applied to many different mechanisms. Figure 1.2 shows the stages of the AMORE 2.0 algorithm. This algorithm, described in Chapter 3, still utilizes a graph theoretical framework, but is different in approach from AMORE 1.0. The first difference is that it is an iterative reduction approach, where the mechanism is reduced piece by piece, rather than building a new mechanism from scratch. In this way, it is more similar to the DRG method, but otherwise it is distinct from both. The AMORE 2.0 algorithm takes a speciescentric approach to mechanism reduction. In DRG, a weak edge on an important species is viewed equally to a weak edge on an unimportant species. This leads to a less than optimal ordering of edges. The first task of the AMORE 2.0 algorithm is to sort the species in order of importance. The primary metric of importance is the yield of each species from the source species. All else being equal, a species’ impact is proportional to its yield. To account for priority species which may have a relatively low yield, but contribute significantly to some other property, such as secondary

7



<!-- Start of picture text -->
Input Mechanism<br>Mechanism representation as  Algorithm Settings and<br>graph Inputs<br>Identification of cycles and<br>groups<br>Species ranking based on<br>Rapid Yield Algorithm<br>yields<br>Merging grouped species<br>Merging categorical species<br>Removing remaining species<br>Optimization of r ate constants Mechanism Error Metric<br>Reaction combination and<br>sti�ness reduction<br>Stoichiometric coe�icient Graph Theory Assisted<br>optimization Gradient Descent<br>Output Mechanism<br>AMORE 2.0 Algorithm<br><!-- End of picture text -->

Figure 1.2: Schematic diagram of the AMORE 2.0 algorithm. Gray indicates mechanisms, green indicates mechanism analysis steps, red indicates mechanism reduction steps, purple indicates mechanism optimization steps, and blue indicates supplemental algorithms or methods to the AMORE 2.0 algorithm.

8

organic aerosol production, those species may be listed as priority species, and will not be removed in the reduction. The yield of all species is measured using a novel graph theory technique which we call the Rapid Yield Algorithm, which is discussed in detail in Chapter 4.

Once the species are sorted, they are removed until a desired mechanism size is reached. The naive approach to species removal would be to remove all instances of that species without making any other changes. This is akin to the DRG method with respect to edge removal. However, any products of the removed species will be disconnected from the rest of the mechanism. Even if those products have other sources, their overall yield will be reduced. Ideally, removing one species would have no impact on the yield of every other species. To get as close to this outcome as possible, we use the method of rerouting, whereby all products of the removed species are now produced by the source of that species. By rerouting chemical pathways to skip reaction generations, we can maintain the yields of remaining species as the mechanism is reduced. The graph theoretical framework for mechanism representation is very useful in this context, as species can be replaced using very simple graph operations, and accounting for the new stoichiometric coefficients of condensed reactions is very straightforward.

In addition to the simple case of species removal, we have also developed methods for merging species together. This can be done in one of two ways. The first method, called grouping, is designed for species that are very similar, usually isomers. The chemistry of these species is merged in proportion to their yields, and the group is represented by the most important of the species in the group. The second method, called categorization, is designed for large groups of loosely related species which share some property, such as a functional group or a propensity for the production of secondary organic aerosol. For each category, a new species is created, and for each species in the category that is removed, its production is rerouted to the new category species. These merging methods serve to simplify chemistry involving multiple similar isomers and represent the behavior of large groups of species.

Another unique aspect of the AMORE 2.0 algorithm is its treatment of strongly connected components. A strongly connected component (SCC) is a set of species where there exists a path

9

from each species in the component to every other species in the component. These SCCs are cyclical rather than unidirectional, and mass transfers between each species in the SCC. These SCCs contribute a small fraction of the total number of species in atmospheric oxidation mechanisms, but they tend to have outsized influence on mechanism dynamics. Rerouting chemistry from these species is not straightforward, as there is no inherent direction to the flow of mass in these components. Accordingly, we have devised a method to track the eventual outgoing flow of mass from each entry point into the SCC to properly reroute chemistry when SCC species are removed. When SCC species are removed, we also ensure that new SCCs are not inadvertently created when removing the species. This is the first reduction method to account for SCCs as different than other species.

When developing this method, we began working with the algorithmically generated GECKOA Camphene mechanism [17]. This mechanism contains 103,694 species, making it 259 times larger than the isoprene mechanism that we worked with for this algorithm. The size of this mechanism is a result of camphene being a larger molecule (C10H18) compared to isoprene (C5H8) and because the GECKO-A algorithm can automatically identify every possible product from a starting species, whereas manually made mechanisms are limited by the labor needed to identify and differentiate products. This mechanism tested the limitations of our algorithm, especially in terms of computational efficiency. When we started out, we were unable to complete the reduction with this mechanism because the code was too slow. However, over time we made each aspect of the code more efficient and now it is able to reduce the camphene mechanism in roughly 30 minutes. By demonstrating a proof of concept with camphene, we are now able to reduce other GECKO-A mechanisms without computational limitations.

In addition to being a submitted manuscript, the AMORE 2.0 algorithm is available for download and use on Github, and is designed to be easily adapted to new mechanisms. Currently, it is being applied to an alpha-pinene mechanism and the Common Representative Intermediates mechanism [57].

The Rapid Yield Algorithm is an essential part of the AMORE project, and has many potential

10

applications outside of the scope of this work. It is discussed in detail in Chapter 4. It is an algorithm which uses the graph representation of the mechanism to estimate the yields of all species in the mechanism without an ODE solver. As such, it does not follow the same computational constraints that ODE solvers do, and is generally more efficient than an ODE solver. While this algorithm has been accurate for our purposes, there are some limitations to the method which we discuss and address in the chapter. In addition, we discuss two modifications to the algorithm which address the time-dependent nature of chemical reaction dynamics.

Throughout this work, we have relied on a testing framework to assess the performance of reduced mechanisms, which is discussed in Chapter 5. The basic performance metric involves running the full and reduced mechanisms in a box model under a range of conditions and comparing the output of priority species in the mechanism. There are many modifications and options therein. We have also been able to run some of our reduced mechanisms externally in chemical transport models, where we are unable to compare to the full mechanism due to computational constraints in running large mechanisms. Instead, we compare to observational data and to existing reduced models.

In parallel to the development of the AMORE 2.0 algorithm, we undertook a collaboration with Arijit Chakraborty of the Venkatasubramanian group, discussed in Chapters 6 and 7. For this work, we developed a method of mechanism reduction that utilizes a hybrid of artificial intelligence and domain specific knowledge, termed hybrid AI. Specifically, we use a genetic algorithm to search for an optimal mechanism structure within a chemically constrained search space. In this way, this method was similar to the AMORE 1.0 method, in that it builds a mechanism from scratch. Genetic algorithms operate by creating a population of candidate individuals (mechanisms in this case), which are selected, mutated, or discarded based on their fitness over the course of several generations, until an optimal result arises. They mimic the process of evolution in nature. This is an efficient search method, because it does not require the precise tuning of each possible parameter, which would be infeasible due to the search space involved. We paired this method with a particle swarm optimization (PSO) of stoichiometric coefficients and rate constants to create a reduced

11

mechanism that was able to exceed the performance of the AMORE 1.2 isoprene mechanism. This work is discussed in Chapter 7. The particle swarm optimization is a useful tool in its own right for reduced mechanism optimization, and so we wrote a separate manuscript for that project which is under review and is available as a prepint [54], and is provided in Chapter 6.

In addition to the particle swarm optimization, we developed a gradient descent optimization tool which utilizes the Rapid Yield Algorithm as the basis for a fitness function rather than a box model, speeding up the optimization significantly. This work was lead by intern Alexander Berman and is discussed in Chapter 8. For this optimization, we developed two graph theory based methods for optimizing stoichiometric coefficients of reduced mechanisms. The first sorts coefficients into groupings in which each coefficient is independent from the other, allowing for a significant reduction in the number of measurements needed to measure the full gradient. The second method sorts coefficients in an order such that the coefficients which impact the fewest outputs are optimized first, in an attempt to find better final mechanisms by optimizing the coefficients in a specific order. Both methods worked well, and we were able to develop a reduced isoprene mechanism that was smaller than the smallest mechanism demonstrated in the AMORE 1.0 paper while maintaining accuracy as a result of the optimization.

The last chapter discusses the optimization inputs to the AMORE 2.0 algorithm. One of the primary inputs to the AMORE 2.0 algorithm, alongside the mechanism itself, is a set of atmospheric conditions relevant to the mechanism. The selection of these conditions has a large impact on the reduced mechanism. This work, which was lead by intern Reese Carter, uses several methods of data clustering to optimize the input conditions from a larger dataset of atmospheric conditions.

12

# **Chapter 2: AMORE v1.0 Isoprene Mechanism**

|**Mechanism**|**Number of species**|**Number of reactions**|**Reference**|
|---|---|---|---|
|MCM 3.3.1|602|1926|[2]|
|CRI 2.2|56|186|[34]|
|Caltech|404|897|[16]|
|Caltech Reduced Plus|131|220|[16]|
|RACM2|9|12|[58],<br>[31]|
|CB6r3|10|17|[59]; [32]|
|AMORE-Isoprene|12|22|This work|



Table 2.1: Sizes of select isoprene mechanisms including the mechanism in this work. Larger mechanism sizes are self-reported. For smaller mechanisms, species and reactions were recounted for this work using the following criteria: i) only species unique to isoprene chemistry are included, which excludes species that do not contain the isoprene carbon backbone ii) All reactions involving species unique to isoprene are counted iii) Heterogeneous reactions involving isoprene species are not counted.

This chapter describes our first attempt at mechanism reduction. In it, we detail the development of methods for mechanism evaluation and using a graph theoretical framework for mechanism reduction. The initial goal was to produce a very reduced isoprene mechanism through algorithmic means that was as good or better than current small mechanisms. Through several rounds of mechanism testing, we discovered that existing reduced mechanisms did a relatively poor job of representing the full isoprene chemistry, and that automated mechanisms with simple construction were able to perform better. Given this, we developed an isoprene mechanism using a graph theory based algorithm designed to create very simple mechanisms. This method resulted in a mechanism structure that was then optimized manually to achieve a well-performing mechanism that was much smaller than the original full mechanism. Once finished, it was tested in the Community Multiscale Air Quality (CMAQ) modeling system [60] along with our box model setup. This mechanism was originally published as the AMORE v1.0 isoprene mechanism, which was

13

then updated twice in subsequent publications.

The algorithm used in this method was limited in scope, due to its inability to select stoichiometric coefficients, limited reduced mechanism size, and specific application to the isoprene system. However, with this method we were able to clearly demonstrate a proof of concept that reduced mechanisms could be produced through automated means and that they could improve upon existing mechanisms.

## **2.1 Methods**

In this section we describe our approach for model reduction and inputs to the process, and the procedure used for testing the reduced mechanism.

In brief, an algorithm was developed to reduce the full isoprene mechanism to a smaller more manageable mechanism that can be used in 3D chemical transport models. The output mechanism from the AMORE algorithm was subsequently adjusted manually to optimize its performance for use in atmospheric modeling. In order to test the AMORE-Isoprene mechanism, a mechanism error metric was devised.

The AMORE-Isoprene mechanism was the product of this methodology. Our novel algorithm was essential in the creation of this mechanism, but requires further work before it can be used for other mechanisms and without manual adjustment.

## 2.1.1 Full Mechanism Input

A “full” chemical mechanism is required for the input to the reduction algorithm. The full mechanism also serves as a benchmark for the accuracy of the reduced mechanism. In this study, the reference isoprene oxidation mechanism was based on [16]. The Wennberg mechanism is a comprehensive compilation of isoprene oxidation chemistry from laboratory and computational studies published up to 2018, including the formation of isoprene epoxydiols (IEPOX) [61], intramolecular RO2 chemistry (autoxidation) [62], and recent advances in isoprene nitrate chemistry [63]. Despite its size and complexity, some branches of the oxidation cascade are truncated in the

14

[16] mechanism due to lack of published experimental constraints, specifically degradation pathways for some later-generation intermediates with 2, 3, or 4 functional groups [30]. Therefore, modeled on the approach used by [16] in preparing the Caltech Reduced Plus mechanism, we expanded the Wennberg mechanism to include degradation of these species. Further details are available in section S.1 including box model comparisons of original and extended mechanisms to EUROCHAMP data [64, 65]. In addition, the extended mechanism is listed in its entirety in section S.19. Briefly, the intermediates were mapped to lumped species in the Caltech Reduced Plus mechanism or species in MCMv.3.3.1, and assigned the corresponding degradation pathway, products and rate constants from that mechanism. For the rest of this manuscript, we refer to this updated mechanism as the _Caltech full mechanism_ . This mechanism was chosen instead of the MCM isoprene mechanism [2], which is of a similar size, because it includes the results of more recent isoprene chamber studies which were not yet published at the time that the current MCM mechanism was developed (e.g., [62]).

## 2.1.2 Priority Species

Given that model reduction necessarily involves removing or lumping chemical species from the mechanism, we identified a set of nine important organic species and eight important oxidant and nitrogen oxide species to be protected from elimination during the model reduction process. This priority species list was an input to the model reduction algorithm. A full table of these species is available in section S.2. Besides isoprene, these species were chosen for their importance for SOA or brown carbon formation and/or expected impact on gas-phase photochemistry (isoprene epoxydiols (lumped), isoprene nitrates (lumped), glyoxal, methylglyoxal, methacrolein, methyl vinyl ketone, peroxyacetyl nitrate, methyl radical, peroxyacetyl radical). Formaldehyde was also included in the protected species list due to its status as an air toxic [66, 67, 68] and for its potential to indicate oxidant levels [69]. Other species such as NO _𝑥_ , HO _𝑥_ , O3, and other oxidants are included in the mechanism as well. The accuracy of the reduced isoprene mechanism is measured by its ability to simulate the time evolution of the concentrations of the priority species and oxidants

15

and nitrogen oxides under different conditions.

## 2.1.3 Reduction Algorithm Development

In general, a new reduced isoprene oxidation mechanism will be a good candidate for application in large scale models if it provides gains in accuracy or computational efficiency. Since a tradeoff exists between mechanism size (and therefore computational efficiency) and accuracy, improvements in one aspect are sought which avoid sacrifices in the other. Therefore, the mechanism should be of similar size and complexity to existing mechanisms (or smaller), and of equal or better accuracy. The most compact isoprene mechanisms, including those currently used in the CMAQ modeling suite (RACM2 and CB6r3), include roughly 10 species unique to the isoprene mechanism and up to 20 reactions (Table 2.1). Note that this list of species does not include all priority species; some, such as IEPOX and isoprene nitrates, are included, whereas others, such as formaldehyde and glyoxal, which lack the isoprene carbon backbone and are also formed through non-isoprene pathways, are not. Thus, an isoprene mechanism of comparable size to existing reduced mechanisms will have around 10 isoprene specific species, around four of which (isoprene, isoprene nitrates, IEPOX, methyl vinyl ketone), are already priority species. The remaining 6 species are isoprene intermediates which are not considered priority species themselves, but play an important role in the dynamics of the isoprene mechanism and the production of priority species.

The AMORE algorithm represents the full mechanism as a graph. Many prior works have utilized graph theory to analyze chemical mechanisms [70, 49, 50, 51, 40, 71]. In this work, nodes represent species, and edges represent a directed relationship between two species, in which one is a reactant and the other a product of the same set of reactions. Prior graph-based reduction methods have focused solely on removing non-essential components of the mechanism (’pruning’ the graph). This work focuses instead on determining the optimal graphical structure of the final reduced mechanism, as constrained by target mechanism size. This is done by determining the essential mechanistic pathways needed to accurately represent the full mechanism in a reduced structure, as discussed below.

16

A mechanistic pathway consists of a set of reactions joined by intermediate species. For a path of N reactions, there are N - 1 intermediates. With the constraint of 6 intermediate species, this allows for roughly 6 paths with 2 reactions each with one intermediate, or 3 paths with 3 reactions each with two intermediates, both options having 6 intermediates. If some pathways are able to share intermediates, then more pathways can be included. It is also our goal that the reduced mechanism structure maps as closely as possible to known reactions with measured rates.

A new algorithm was designed specifically to develop optimal mechanisms of roughly 10 total species, 6 intermediate species, and 20 reactions. At a high level, the algorithm identifies a small set of the most important mechanistic pathways in the full mechanism, and concatenates them in order to reduce the number of intermediate species. The algorithm estimates the importance of a given mechanistic pathway by determining the impact each possible pathway has on the yields of priority species. The mechanism reduction algorithm has four main components: (1) a sub-algorithm to rapidly estimate the yields from isoprene of priority species under constant oxidant and nitrogen oxide concentrations and atmospheric conditions (yield estimation algorithm, Section 2.1.3), (2) a sub-algorithm to assess the importance of different pathways given the yields of priority species (pathway importance algorithm, Section 2.1.3), (3) a sub-algorithm for optimally combining pathways to reduce intermediate species (pathway combination algorithm, Section 2.1.3), and (4) a sub-algorithm to estimate yields of priority species for each pathway in the mechanism (priority species yield determination, Section 2.1.3). The overall AMORE algorithm process is shown in Figure 2.1. All sub-algorithms are described in detail in the following sections.

## **Yield Estimation Algorithm**

The yield estimation algorithm utilizes graph theory, and takes advantage of the relatively small number of cycles (a path in the graph that starts and ends at the same species) and small number of reactions with two carbon-containing reactants in the isoprene oxidation scheme. It rapidly estimates the yields of all species from isoprene in the full mechanism, assuming the complete oxidation of isoprene and its products. The algorithm emulates the full mechanism so that the

17

#### 1. Yield Estimation Algorithm

lsoprene — Yucuo + Yiepox + ... = Y = priority species yields

WHCHO x YHCHO + WiEPOx x YieEPox +... = W°¥ = weighted priority species yields

#### 2. Path Importance Algorithm

Y{OH, NO} = Y(elevated [OH], elevated [NO], else baseline) |= min (w-Y{QH, NO} - w-Y{OH}, w-Y{OH, NO} - w-¥{NO})

### 3. Path Combination Algorithm



<!-- Start of picture text -->
ee< O<br>HO<br>ee => ee<br><!-- End of picture text -->

### 4. Priority species yield determination

ee Y{OH, NO} HO™ Y{OH, HO>}

numerical simulation need not be run repeatedly during sensitivity testing. The algorithm begins by representing the full mechanism as a directed graph. The directed nature of the representative graph delineates the direction of the flow of carbon over time. Cycles are unique instances in this context, in which carbon flows in two different directions and it is not necessarily evident which direction dominates. The algorithm takes oxidant and nitrogen oxide concentrations (OH, HO2, O3, MO2, NO, NO2, NO3), which are treated as constant, solar intensity, temperature, and pressure as inputs, and calculates the flux of carbon through the mechanism pathways using the rate law information provided. Since this algorithm is dependent on oxidant and nitrogen oxide concentrations and other atmospheric parameters, it can be used to determine how yields are impacted by relevant atmospheric conditions.

The full mechanism is approximated using a directed acyclic graph (DAG). In order for a mechanism to be represented as a DAG, it must contain no cycles and reactions with two reactants must be broken into two sets of edges for each reactant, because edges can only represent the relationship between two species. For example, a reaction with two reactants and one product would become two edges, one for each reactant connecting to the product. Oxidant and nitrogen oxide concentrations are approximated to be constant, so reactions involving them are treated as pseudo first-order. Cycling in the isoprene oxidation system mainly takes place among oxidant and nitrogen oxide species, which are only represented implicitly in the graph. For cycles involving isoprene oxidation products, all species in the cycle are combined into one ’super node’. The incoming and outgoing edges of the super node include all edges of all species that it represents. The method used to reduce cycles to super nodes is described in section S.4.1.

The DAG structure is then utilized to calculate the partitioning of carbon between branches within the graph, ultimately giving an estimated yield for each oxidation product species. This novel approach takes advantage of the graphical representation of the mechanism to rapidly approximate yields which would otherwise require a box model to calculate. The resulting time savings allows a much larger set of input conditions to be tested than would be feasible with a box model. The yield is defined as the moles of each species produced per mole of isoprene reacted.

19

Starting from a species of known yield, the yield of a direct product can be calculated as the rate constant involving said product over the sum of all rate constants reacting with the starting species. The yield for a species A from isoprene, _𝑌𝐴_ , is calculated as follows:





where _𝑌𝑖_ is the yield of species i from isoprene, and _𝑌𝐴,𝑖_ is the yield of species A from species _𝑖_ , _𝑁_ is the number of species, _𝑅_ is the number of reactions, _𝜈𝑖,𝑟_ is the stoichiometric coefficient of species _𝑖_ in reaction _𝑟_ , and _𝑘_<sup>_𝐼_</sup> is the (pseudo) first order rate constant, that is, _𝑘_<sup>_𝐼_</sup> = _𝑘_<sup>_𝐼𝐼_</sup> [ _𝑜𝑥𝑖𝑑𝑎𝑛𝑡_ ] for oxidation reactions, or else the first order rate constant for photolysis and isomerization reactions. The yield of any species can be estimated once the yields of all its parent species in the graph are determined. Thus, with the assumptions and inputs outlined above, an estimate of the yield of all species from isoprene can be obtained for a given set of inputs. Running in a Jupyter notebook environment on a personal computer with a 1.8GHz dual-core Intel Core i5 processor, it takes roughly 0.06 seconds for the algorithm to estimate all yields for a given set of conditions, 50x shorter than a box model run time of the full mechanism. This is a valuable tool for rapidly probing large mechanisms to study their outputs under a variety of inputs.

The yield estimation algorithm was tested for accuracy by comparing estimated yields to box model simulated yields for the range of conditions used for model development. A detailed analysis of the yield estimation algorithm accuracy is available in section S.4.2. A visualization of the yield estimation algorithm is shown in Figure S.8.

## **Pathway Importance Algorithm**

With the yield estimation algorithm in place, we developed a method to identify and evaluate the importance of paths within the mechanism. Given the constraints on the size of the final

20

reduced mechanism discussed, the total number of paths will vary depending on the number of intermediates that can be shared between paths. The full mechanism contains long, highly branched paths with multiple end products. Thus, no existing pathways within the full mechanism satisfy the design constraints. Instead, model paths were created in which each path was represented by a sequence of reactions with one of the possible oxidants or nitrogen oxides: OH, NO, NO2, NO3, HO2, O3, methyl peroxy radical (MO2), or else photolysis. There was no requirement for a given path to be in the full mechanism, rather paths recreate the oxidant and nitrogen oxide dependent outcomes for the priority oxidation products. Each path was constrained to contain only irreversible reactions, with each oxidant or nitrogen oxide appearing no more than once (this constraint was lifted during the manual adjustment process). The justification for these simple paths is that isoprene oxidation product concentrations can be thought of as functions of isoprene, oxidant, and nitrogen oxide concentrations, and each path represents a scenario in which a set of oxidants and nitrogen oxides are favored. Thus, by containing multiple different paths, the priority species yields can be varied based on the oxidant and nitrogen oxide concentrations. For example, a path of {OH, NO} represents the reaction of OH or NO with isoprene to create a hypothetical intermediate, and the reaction of the other oxidant or nitrogen oxide (either NO or OH) with that intermediate to form isoprene oxidation products. This path would be favored when OH and NO concentrations are high, and allows for a unique distribution of priority species yields under these conditions. There were 256 possible paths, represented by non-duplicate combinations of the possible oxidants or nitrogen oxides. Temperature and pressure are other parameters that significantly influence isoprene chemistry. However, these parameters are implicit to the graph as inputs to calculate rate constants. Thus, temperature and pressure were not represented explicitly in the algorithm, leaving rate constants to be determined either through calibration or through direct reaction analogues in the full mechanism. The default temperature and pressure for yield estimates were 292 K and 1000 hPa respectively.

Using the yield estimation algorithm, a measure of the importance of each path was determined by evaluating the product yields for a sequence of inputs designed to probe the sensitivity to each

21

|**Parameter**|**Baseline Value**|**Elevated Value**|
|---|---|---|
|Temperature (K)|292|-|
|Pressure (hPa)|1000|-|
|Solar Intensity (unitless)|0|1|
|OH (ppb)|1e-6|1e-4|
|NO (ppb)|1.17e-6|0.53|
|NO2(ppb)|1e-4|0.01|
|NO3(ppb)|2.3e-4|0.02|
|HO2(ppb)|0.04|0.2|
|O3(ppb)|16.7|100|
|MO2(ppb)|0.1|0.2|



Table 2.2: Baseline and elevated values of input parameters used in the pathway importance algorithm, a component of the AMORE algorithm.

oxidant, nitrogen oxide, or photolysis. Each oxidant and nitrogen oxide was assigned a baseline concentration or intensity, determined from atmospherically relevant ranges in which rates of reactions involving each species were similar. For example, the baseline concentrations of O3, OH, and NO3 were set such that the rate of reaction of isoprene with each oxidant or nitrogen oxide would be the same. Input sequences were created in which the concentration of each oxidant and nitrogen oxide (or photolysis intensity) within the path is elevated, in turn, roughly one order of magnitude above the baseline. Table 2.2 shows the input values used for the path importance algorithm. All possible combinations of each high and low value were used as an input space, resulting in 256 different input conditions. The goal in selecting input conditions was to find values that were relatively low and relatively high without biasing the algorithm with extreme values. They do not represent the full range of values that each input takes. The AMORE-Isoprene mechanism performs satisfactorily under more extreme conditions than those that were used as input conditions to the algorithm, but it would be possible to create a mechanism optimized for a more extreme scenario using the AMORE algorithm. We conducted a sensitivity test of the pathway importance algorithm to a select set of changes to the inputs shown in Table 2.2. Specifically, elevated concentrations of OH, NO, and NO2, were adjusted to reflect realistic upper values for these species. The results of this test are given in Section S.13 and Table S.5.

For each hypothetical path, the yield of priority species from that path was determined by

22

elevating the input values of the oxidants or nitrogen oxides in the path. A path was considered important if this process resulted in yield estimates that differed significantly from the baseline. Multi-step path yields were evaluated in comparison to paths with one less elevated oxidant or nitrogne oxide step. For example, the path {OH, HO2, NO} was compared to the paths {OH, HO2}, {OH, NO}, and {HO2, NO}. If the yield of priority species differed significantly from all of the compared paths, then the path was deemed important. The importance of each path was ranked in terms of the magnitude of difference in yield of the path to the least different shorter path. This method ensured that every component of the path was necessary to produce unique yields compared to the baseline. Equation 3 shows the importance metric used to choose the most important paths,



where _𝐼_ is the path importance, _𝑁_ is the number of species in the important species list, _𝑖_ is an individual important species in the list, _𝑌_<sup>0theyieldofspecies</sup><sup>_𝑖_fromisopreneforthe</sup> _𝑖,𝑖𝑠𝑜𝑝_<sup>is</sup> path being measured, _𝑌_<sup>_𝑥_theyieldofspeciesifromisopreneinpathx,</sup><sup>_𝑚𝑎𝑥_(</sup><sup>_𝑌𝑖,𝑖𝑠𝑜𝑝_)isthe</sup> _𝑖,𝑖𝑠𝑜𝑝_<sup>is</sup> maximum yield obtained by species _𝑖_ from the yields of all paths, and the path list is the set of paths with one less elevated oxidant or nitrogen oxide than the path being measured.

## **Pathway Combination Algorithm**

Using this path analysis, the following 8 paths were identified and incorporated in the mechanism: {O3}, {NO3}, {NO3, HO2}, {NO3, HO2, hv}, {NO3, NO}, {OH}, {OH, HO2}, {OH, NO}. The number of paths was chosen based on the desired mechanism size, but the paths were determined by the pathway importance algorithm above. In order to reduce the number of intermediates, paths were joined together such that any shared oxidant or nitrogen oxide within paths had a shared intermediate. For example, all paths involving OH were structured so that the first reaction was with isoprene and OH which then formed a shared intermediate. The reaction paths were algorithmically structured to share as many intermediates as possible. The pathway combina-

23

tion algorithm started by grouping paths by a shared intermediate. For example, the paths {NO3}, {NO3, HO2}, {NO3, HO2, hv}, and {NO3, NO} all share a common NO3 reaction step. There are instances in which there are multiple ways in which to group pathways. For example, {OH, NO} can either be grouped with other OH containing pathways or with NO pathways. There was no algorithmic way to prioritize these two options. This is an instance in which manual intervention is required to assign preference between pathway groupings. This can be done by simply choosing the order in which the pathway reactions should occur. For example, choosing the order {OH, NO} would group this pathway with other OH pathways, whereas choosing the order {NO, OH} would group this pathway with other NO pathways.

Once the groupings are formed, an initial reaction step is created in which isoprene reacts with the commonly shared oxidant or nitrogen oxide to form an intermediate shared by all of the pathways. For example, in the NO3 pathway grouping, the reaction of isoprene with NO3 is shared with all pathways, which subsequently branch from each other. Pathways that share two oxidants or nitrogen oxides, such as {NO3, HO2} and {NO3, HO2, hv} share two intermediates. By grouping pathways by shared oxidants and nitrogen oxides, and creating sub-groupings for multiple shared oxidants and nitrogen oxides, the pathway combination algorithm creates a reduced mechanism structure. This algorithm does not allow for the recombination of branched pathways, meaning that the resulting reduced graphs are necessarily trees. Figure S.1 demonstrates the combination of all of the identified paths to form the reduced mechanism structure.

## **Priority Species Yield Determination**

The yield of each priority species is measured for each path using the yield estimation algorithm (see Section 2.1.3). These yields are used as stoichiometric coefficients for the product terms of the terminal reaction of each path. All priority species are considered eligible as product terms of the terminal reaction of a given path. For each path, the terminal reaction is defined as the reaction in which no additional intermediates were produced. For example, the path {OH} contains the reaction of isoprene with OH to form isoprene hydroxy peroxy radical as an intermediate

24

(reaction 1 in Table S.2). This pathway was then given a terminal reaction, involving the first order decomposition of the isoprene peroxy radical in order to produce the final priority oxidation products (reaction 2 in Table S.2). The stoichiometric coefficients of each oxidation product were the yields as estimated by the yield estimation algorithm.

This algorithm completed the automated portion of the mechanism development process. The fully automated mechanism is described in Table S.2. The assignment of reaction rate constants and species naming are discussed in the following section. The subsequent manual optimization process for direct implementation into 3-D atmospheric models is described in Section 2.1.4.

## **Rate Parameter Identification and Species Naming**

Once the skeletal reduced mechanism was established, rate parameters and species names were identified manually. The first step was to identify any direct analogues between mechanisms in the reduced mechanism and known reactions (i.e., those in the Caltech full mechanism). There were many reactions with direct analogues, including all reactions involving isoprene. In these cases, the rate law and parameters assigned were identical to the original.

For reactions without direct analogues, the reaction was typified by the oxidant or nitrogne oxide involved. In the Caltech full mechanism, reaction rate laws with the same oxidant or nitrogen oxide tend to have a similar form and fall under a limited range of parameter values. Where there were multiple possible reaction forms, the most common form was chosen. After choosing the form of the rate laws, parameters were tuned by running box model simulations under conditions that favored the reaction being tested. The parameters were calibrated to match the concentration profiles of dominant products in comparison to the Caltech full mechanism. A list of all rate laws and parameters, their analogues, and the method of selection is given in Table S.3.

All species names listed in the AMORE-Isoprene mechanism were manually identified after the completion of the automated mechanism reduction process. As with the rate law selection process, the first step was to identify direct analogues in the full mechanism. Since the AMOREIsoprene mechanism is highly reduced, all species with the exception of isoprene represent groups

25

of species in the Caltech full mechanism. Thus, direct analogues were generally analogous groups of species. For species without a clear analogue, naming was based on the oxidants and nitrogen oxides that reacted to form the species. From this information, a name was assigned based on the predicted functional groups present in the species. For CMAQ modeling, the naming convention is different for some species due to their prior existence in the model. Table S.4 gives each species name for this paper and for CMAQ, the analogues it represents, and the functional groups involved.

## 2.1.4 Manual Mechanism Optimization and Evaluation

The algorithmically generated isoprene mechanism was manually optimized for use in the CMAQ modeling environment and evaluated for its performance compared to other reduced mechanisms. The optimization process was done using the F0AM box model (Section 2.1.4) and the CMAQ testing environment (Section 2.1.4), and the manual optimization process is described in Section 2.1.4. The graph theoretical framework helped inform our decisions in this process. For example, the conceptualization of the mechanism as a set of unique pathways connected by sequences of reactions, which is rooted in graph theory, helped us to categorize reactions and how adjustments to their parameters would impact end results under different testing conditions.

In the process of evaluating the mechanism, an error metric was developed and used for quantitative comparisons between mechanisms (Section 5.2). In the optimization and evaluation phase, the Caltech full mechanism was used as a baseline for comparison, along with experimental chamber data for further corroboration [61].

Higher priority was put on mechanism accuracy rather than retention of the original algorithmically generated mechanism structure. Thus, changes were made that deviated from the algorithmically generated mechanism, however the core components of the algorithmically generated mechanism, including a majority of the identified important paths, were retained, and the algorithmically generated mechanism provided an essential functional starting point from which to improve the final mechanism performance.

26

## **Box Model Testing**

The Framework for 0-D Atmospheric Modeling (F0AM) [72] was used to simulate isoprene mechanisms for the purpose of evaluating the AMORE-Isoprene mechanism. 0-D box model testing was done in two primary phases. The first phase was aimed at optimizing the AMOREIsoprene mechanism. The Caltech full mechanism was taken as the most accurate mechanism for ground truth, and RACM2 was used as a benchmark for comparison. Simulated concentration profiles of key species such as NO _𝑥_ , HO _𝑥_ , IEPOX, O3, and formaldehyde were analyzed in order to assess the AMORE-Isoprene mechanism. The goal was to match both the magnitude and form of each species concentration in the Caltech full mechanism. A detailed description of the matching process is provided in Section 2.1.4.

The second phase of box model testing involved quantitative comparisons between mechanisms for demonstration of the performance of the AMORE-Isoprene mechanism. The mechanism was tested in the F0AM environment alongside the Caltech full mechanism, RACM2 isoprene mechanism used in base CRACMM1, Carbon Bond 6 revision 3 (CB6r3), and the Caltech reduced isoprene mechanism. An error metric was created to determine the degree of matching between two concentration curves. This error metric was averaged over many species and conditions to create an overall mechanism error metric. Section 2.4.3 gives a detailed description of the error metric developed for this study.

A set of six input conditions were devised to simulate the mechanisms. Given that isoprene oxidation is split into three main pathways of reaction with OH, NO3, and O3, these three pathways must be represented in the chosen testing conditions. Subsequent oxidation with NO is particularly important in the OH pathway, and low light conditions are important in the NO3 pathway. Given this, the first five conditions were low NO _𝑥_ , high NO _𝑥_ , high O3, high NO3, and high NO3 + low hv. The final input condition was set to simulate the chamber study of [61], allowing for the pairing of box model results to experimental results. In that study, H2O2 photolysis was used as the source of OH, and small amounts of NO _𝑥_ were measured as well. For all F0AM simulations, H2O2 was used as the source of OH (which allowed for OH to be a dynamic quantity), and NO was used as

27

|**Species**|**Chamber Comp.**|**Low NO**_𝑥_|**High NO**_𝑥_|**High NO**3**, low hv**|**NO**3|**High O**3|
|---|---|---|---|---|---|---|
|isoprene (ppb)|92.5|10|10|10|10|10|
|H2O2(ppb)|1660|200|200|0|100|200|
|NO (ppb)|1|0.5|5|2|1|0.5|
|O3(ppb)|0|0|0|0|0|100|
|NO3(ppb)|0|0|0|**0.02**|**0.02**|0|
|hv(unitless)|3.5|3.5|3.5|0.5|3.5|3.5|



Table 2.3: F0AM box model testing input conditions used for calculating the error metric and evaluating the AMORE-Isoprene mechanism. Bolded values represent species concentrations that were held constant. All other concentrations varied with time after initiation of the simulation.

a source of NO _𝑥_ . For ozone and NO3 the concentrations were set directly. Due to the lack of NO3 cycling and the resulting rapid decay of NO3, NO3 concentrations were held constant in for high NO3 conditions in order to favor this pathway through the duration of the simulation. Temperature and pressure were held at 292 K and 1000 hPa for all conditions. This corresponds to low elevation warm conditions that are most relevant for isoprene chemistry. The rate of photolysis reactions are scaled by a unitless parameter labeled as hv. The value of this parameter was calibrated to match results of [61] chamber data for high photolysis conditions. Table 2.3 shows the inputs for each of the six conditions.

## **CMAQ Modeling**

CMAQ v5.3.3 [73] with additional updates as in Place et al. (in prep) was used to conduct simulations over the northeastern U.S. for June through August 2018 (May 2-31 used as spinup) at 4km by 4km horizontal resolution. Baseline gas and aerosol-phase chemistry was specified by CRACMM version 1 (Pye et al., in prep) which uses the RACM2 representation of isoprene chemistry [58]. Additional simulations were conducted in which CRACMM’s isoprene chemistry was replaced with AMORE-Isoprene. Meteorology was obtained from WRF v4.1.2 [74] and processed through the Meteorology-Chemistry Interface Processor version 5 [75]. Boundary and initial conditions were mapped from previous work using CB6r3 [74], and emissions were respeciated for CRACMM with additional updates for volatile chemical products [76]. Biogenic emissions were estimated with the Biogenic Emission Inventory System (BEIS) [77] with M3dry [78] used for

28

deposition. CMAQ output was compared to EPA Air Quality System (AQS) and other monitoring network data using the Atmospheric Model Evaluation Tool (AMET) [79]. CRACMM was selected as a baseline mechanism due to concurrent development of AMORE-Isoprene and the CRACMM mechanism for use in EPA research. CRACMM indicated relatively consistent predictions of gas-phase ozone chemistry as other current mechanisms (Place et al. in prep), signifying that the choice of CRACMM as the baseline mechanism for 3-D modeling was unlikely to confound the AMORE-Isoprene results.

IEPOX has heterogeneous chemistry in CMAQ (reactive uptake leading to SOA) following [80] with updates in [81] and [7]. The first generation isoprene organic nitrate heterogeneous heterogeneous chemistry (leading to HNO3 and gas-phase alcohols) was implemented in this work and is specific to AMORE (not in base CRACMM1).

In CMAQ, the species in AMORE undergo deposition. All species that were already present in the base CRACMM1 mechanism were treated the same as in CRACMM1. IPN and IPC were both wet deposited with Henry’s law coefficients predicted by OPERA [82]. In addition, the species were dry deposited using species-specific diffusivities, mesophyll resistances, and LeBas molar volumes [81].

## **Manual Mechanism Adjustment**

In this section we discuss manual adjustments to the algorithmically generated mechanism. To make adjustments, we tested the AMORE mechanism in box model simulations (Section 2.1.4) and 3D Chemical transport simulations (Section 2.1.4). The testing process highlighted issues with the mechanism initially produced by the reduction algorithm that could be corrected via manual adjustments. This process has informed future algorithm development, since the ultimate goal is to automatically generate mechanisms which require no manual adjustment. The structural differences between the automated (labelled as AMORE-NoAdjust) and manually adjusted (labelled as AMORE-final) mechanisms are shown in Figure 2.2. The corresponding reaction numbers from Table 2.4 are shown in the AMORE-final structure. Reaction 13-17 are not shown in the structure

29



<!-- Start of picture text -->
AMORE-NoAdjust AMORE-final<br>Os,es»<br>-es 1<br>On \nos org, OH. \\Nos, 2<br>HO2/@ no/ \Hos 21,22-—€& Noy \ Hoa7<br>/\\no 4 Ho. 4/busve c><br>+ Qo \rs<br>re 12/ \on i \pH 10<br><!-- End of picture text -->

the reversible reaction to terminate into final products, a reaction of the second intermediate with OH was added. The addition of these two reactions did not change the overall nature of the path {OH, HO2} in terms of the oxidants present, but added necessary complexity to the dynamics of the path, resulting in more accurate product differentiation in OH dominant conditions.

It was also observed that NO _𝑥_ concentrations were relatively low compared to the Caltech full mechanism in low NO _𝑥_ regimes in which the OH, HO2 pathway was dominant. To ameliorate the lower NO _𝑥_ concentrations, an additional intermediate called IPC was created for the purpose of reacting with NO to create additional NO2 and NO. This addition is shown in reaction 11 where IPC is a product, and reaction 13, where NO and NO2 are cycled. The effect of this addition is to increase NO _𝑥_ under low NO _𝑥_ conditions, and thus increase ozone, leading to reduced ozone underestimation compared to the Caltech full mechanism.

In addition to box model testing, 3D chemical transport modeling using CMAQ (Section 2.1.4) informed structural adjustments to the AMORE mechanism. These adjustments centered on the treatment of IHN (isoprene hydroxy nitrate, the intermediate of the reaction of ISOP (isoprene hydroperoxy radical) and NO (reaction 5 in Table 2.4, as part of the {OH, NO} pathway) in the mechanism. IHN was not initially identified as a priority species during algorithm development, and thus was not included as an intermediate. Instead, the reaction of ISOP and NO contained no intermediates and led directly to the production of priority end products. However, it was determined that IHN should be given priority based on recent research highlighting its importance in NO _𝑥_ cycling [83]. Thus, IHN was added as an intermediate, and an additional decomposition reaction with OH was added (reaction 10 in Table 2.4). This decomposition reaction led to the production of IEPOX and isoprene nitrates, which were originally produced directly from the reaction of ISOP with NO. Thus, the {OH, NO} pathway was expanded on by adding an additional OH reaction step for the decomposition of IHN. This change is shown in the {OH, NO} pathway with an addition of an OH reaction step in Figure 2.2. In addition to decomposition into other organics, IHN acts as a sink for NO _𝑥_ . This was represented by the addition of reaction 16 in Table 2.4, which did not involve any oxidants or nitrogen oxides as reactants. It was observed that the

31

|#|**Reaction**|**Rate Constant**<br>|
|---|---|---|
|1|ISO + O3 = 0.07 MACR + 0.189 MVK + 0.25 HO + 0.25<br>HO2+ 0.58 HCHO + 0.08 MO2+ 0.1 ACO2+ 0.09 H2O2+<br>0.1 MACP + 0.461 MACR + 0.14 CO + 0.28 ORA1 + 0.15<br>OLT|1.58E-14 exp(-2000/T) cm<sup>3</sup> mol<sup>−1</sup> s<sup>−1</sup><br>|
|2|ISO + NO2= INO2+ 0.3 HCHO + 0.3 NO2+ 0.3 ISON|2.95E-12 exp(-450/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|3<br>4|ISO + HO = ISOP + 0.02 MO2<br>ISOP + HO2= ISHP + 0.6 HO2+ 0.15 HCHO|2.69E-11 exp( 390/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup><br>4.5E-13 exp(1300/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|5|ISOP + NO = 0.14 IHN + 0.7 HCHO + 0.44 MVK + 0.88<br>HO2+ 0.78 NO2+ 0.28 MACR + 0.021 GLY|2.7E-12 exp(350/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|6|ISHP + HO = ISOP|4.6E-12 exp(200/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|7|INO2+ HO2= IPN + HO|3.14E-14 exp( 580/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|8|INO2 + NO = 0.2 ISON + 0.9 HCHO + 0.5 MGLY+ 0.8<br>MVK + 0.5 NO2+ HO2+ 0.1 MO2|9.42E-16 exp( 580/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|9|IPN + HO2= 0.2 ISON + 0.8 NO2+ 0.4 HCHO + 0.05 GLY<br>+ 0.1 MGLY + 0.4 MACR + HO2+ 0.94 MVK + 0.1 MO2|3.4E-11 exp(390/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|10|IHN + HO = ISON + HO + 0.2 IEPOX|2.4E-7 exp(580/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|11|ISHP + HO = 0.05 IPC + 0.15 HCHO + 0.05 MGLY + 0.15<br>MACR + 0.02 GLY + 0.2 MVK + 0.4 NO2 + 0.58 IEPOX<br>+ 0.8 HO|2.97E-11 exp( 390/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|12|ISHP = 0.4 HCHO + 0.1 MGLY + 0.06 ACO2|Photol(HCHO_RAD_RACM2) s<sup>−1</sup><br>|
|13|IPC + NO = 0.35 NO2+ 0.8 NO|1e-10 cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|14|ISON + HO = CO + 0.12 NO2|5e-11 cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|15|ISON + NO2= CO|2e-14 cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|16|IHN = HNO3|2.3e-5 s<sup>−1</sup>|
|17|IEPOX + HO = HO|5E-11 exp(-400/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|18|ISOP + MO2= HO2+ 1.31 HCHO + 0.159 MACR + 0.250<br>MVK + 0.250 MOH + 0.250 ROH + 0.023 ALD + 0.018<br>GLY + 0.016 HKET|3.4E-14exp(221/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|19|ISOP + ACO3= 0.5 HO2+ 0.5 MO2+ 1.048 HCHO + 0.219<br>MACR + 0.305 MVK + 0.5 ORA2|8.4E-14 exp(221/T) cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|20|ISOP + APIP2 = 0.96 HOM + 0.48 ROH + 0.48 HCHO +<br>0.48 MVK + 0.48 HO + 0.48 HO2+ 0.04 ELHOM|1e-10 cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|21|ISOP + APINP2 = 0.96 HOM + 0.48 ROH + 0.48 HCHO +<br>0.48 MVK + 0.48 NO2+ 0.48 HO2+ 0.04 ELHOM|1e-10 cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|
|22|ISOP + LIMNP2 = 0.96 HOM + 0.48 ROH + 0.48 HCHO<br>+ 0.48 MVK + 0.48 NO2 + 0.48 HO2 + 0.04 ELHOM|1e-10 cm<sup>3 </sup>mol<sup>−1 </sup>s<sup>−1</sup>|



Table 2.4: The AMORE-Isoprene mechanism reactions and rate constants. Mechanism specific species are listed in the text.

32

reaction of IPC with NO (reaction 13 in Table 2.4) outcompeted IHN for NO, and thus the yield of IPC (reaction 11) was changed from 0.3 to 0.05 from ISHP. This change came at the expense of NO _𝑥_ cycling under low NO _𝑥_ conditions, however, it was observed that simulated NO _𝑥_ levels were largely the same between AMORE-Isoprene and the base CRACMM mechanism, suggesting that this adjustment would be a net benefit to the overall performance.

Additional reactions of the OH pathway with organic radicals (methyl radical, peroxyacetyl radical, and lumped terpene radicals) were added directly from the RACM2 mechanism. They were not identified as important by the AMORE mechanism, likely a result of the inputs chosen, but came at little additional computational cost since they did not require the addition of any intermediates. These added organic radical reactions allowed for product differentiation in environments where organic radical concentrations are significant.

Finally, the {NO3, HO2, hv} path was determined to be unnecessary due to the relatively small amount of flux carbon directed to it. Instead, the paths {NO3, HO2, HO2} and {OH, HO2, hv} were used in its place. The {NO3, HO2, HO2} path was a variant on the existing {NO3, HO2} path. The {OH, HO2, hv} path was added to represent any potential variation attributed to photolysis in the low NO _𝑥_ regime. All of the above changes are shown in Figure 2.2.

The stoichiometric coefficients of the products in the reduced mechanism were initially assigned based on the estimates given by the yield estimation algorithm, and then optimized manually. Notably, stoichiometric coefficients for oxidant and nitrogen oxide species as products, although clearly important, were not treated in the algorithm due to their implicit representation in the mechanism graph. Thus, while oxidants and nitrogen oxides were included in the algorithm as reactants, they were omitted as products, which reduced their overall accuracy. In particular, the relationship between HO _𝑥_ , NO _𝑥_ and O3 is very sensitive to changes in the isoprene mechanism and is important for determining yields of many other species. These oxidants and nitrogen oxides are of a high order of importance for mechanism accuracy, and so the manual adjustment of their presence in the mechanism was critical. Two clear examples of this are shown in Figure 2.3. Prior to the adjustment shown in Figure 2.3.a, HO2 was significantly reduced in the AMORE-Isoprene

33

mechanism under low NO _𝑥_ conditions. It was observed that reaction 4 (Table 2.4) involving isoprene hydroxy peroxy radical (ISOP) was the main sink for HO2, and by adding HO2 to the product term, the accuracy was significantly increased. This original discrepancy likely reflects a cycling achieved by multiple reactions in the full mechanism that it was not possible to include in the reduced mechanism. Adding HO2 to the product term was the only available way to have good agreement with the full mechanism. The reaction of isoprene hydroxy peroxy radical (ISOP) with NO was another reaction for which oxidant and nitrogen oxide cycling was very impactful. The addition of NO2 and HO2 to the products of reaction 5 (Table 2.4) was used to improve the accuracy of the AMORE-Isoprene mechanism. A demonstration of the adjustment improvements is shown in Figure 2.3.b. Further tests of the adjustments in Figure 2.3 are given in section S.17.

All of the above adjustments were motivated by a clear improvement in mechanism performance that accompanied the change. See sections S.8 and S.9 and Tables S.3 and S.4 for description of rate constants and species names.

All product stoichiometric coefficients were optimized for the accuracy of all priority species in a method similar to that shown for oxidants and nitrogen oxides in Figure 2.3.

## **Mechanism Error Metric**

For inter-comparison of reduced mechanisms, full mechanisms, and experimental data, it was necessary to devise an accuracy metric based on the priority species and other measurable parameters. In the case of the isoprene mechanism, we focus on atmospheric oxidants and nitrogen oxides, organic aerosol, and other pollutants, namely formaldehyde and ozone.

In order to measure these parameters and create an accuracy metric, three steps were taken. The first was to define an error function for comparing the concentration of a species between two mechanisms in a box model simulation. The second was to determine the set of input conditions needed to capture the desired range of performance in the mechanism. The third step was to average errors across species and conditions in order to come up with a final metric. The error function for the comparison of concentration profiles of one species between two mechanisms

34

a) Original: ISOPOO + NO = 0.2 IHN Update: ISOPOO + NO = 0.2 IHN + 0.78 NO2 + 0.88 HO2



<!-- Start of picture text -->
0.8<br>—8—CalTech a 0-08-80<br>008 ot<br>0.6 —4— AMORE Pa<br>2 EN = GP<br>Soak; ‘ < 0.02 spFl 0oA<br>oF= 0.2 3}~~ fe)* 0.01 almanne<br>0 A Otel stele gine ae a a 4 t<br>) 5 10 15 20 0 5 10 15 20<br>Model Time (h) Model Time (h)<br>b) Original: ISOPOO + HO, = ISOPOOH<br>Update: ISOPOO + HO, = ISOPOOH + 0.6 HO,<br>_ a en = a<br>\ —*— AMORE wi update 0.05 ye<br>0.04% ~*~ AMORE f earner<br>a |4 Bou; "ae<br>a _s Qa Ps &<br>20.03 x od0.03; #7 &<br>2 0.02 Xs . ¢ 0.02 j<br>0.01 AgSeSoon | 0.01) f<br>0 VBA sana nnn a nnnnncisil 0 : F<br>1 2 3 4 5 0 5 10 15 20<br>Model Time (h) Model Time (h)<br><!-- End of picture text -->

formed the basis of the accuracy metric. The goal was to devise an error function which is bounded, so the natural choice was to normalize the error. In addition, for the purpose of averaging, the error function needed to always be positive to avoid canceling out errors. From this an error metric was defined shown in Equation 4.



Where _𝐸_ is the error, _𝑡_ 0 is the initial time, _𝑡 𝑓_ is the final time, _𝑇_ ( _𝑡_ ) is the concentration profile being tested and _𝑅_ ( _𝑡_ ) is the reference concentration profile. This concentration error metric ranges from 0 to 1 where 0 is no error and 1 is infinite error. Figure S.3 illustrates the behavior of the error metric for a sample set of profiles.

Although many important species are tracked in the isoprene mechanism, not all species contribute equally to observable parameters. A weighting scheme was devised to capture the relative importance of some species over others. The three main groupings that were included in the weighting scheme were oxidants and nitrogen oxides, priority pollutants, and isoprene SOA species. Each grouping was given an equal contribution to the overall error. The primary oxidant and nitrogen oxide species are OH, HO2, NO and NO2. NO3 is not involved in any significant cycles and is excluded from the oxidant and nitrogen oxide weighting scheme, but still participates in the mechanism. The organic oxidants methyl radical and peroxyacetyl radical are of lesser importance than the primary oxidants and nitrogen oxides and are given a lower weighting. NO, NO2, OH and HO2 are all given a 7% weighting for the overall accuracy. The methyl radical and peroxyacetyl radical are given a weighting of 2.5% each for a total of 33% for oxidants and nitrogen oxides. Ozone and formaldehyde are classified as pollutants, and both are given a weighting of 17% for a total weighting of 34%. The formaldehyde error is multiplied by the fraction of maximum formaldehyde concentration for a given input condition over the average maximum formaldehyde concentration over all input conditions. This gives formaldehyde more weighting as its relative concentration increases.

According to [30], average isoprene SOA contribution is divided up into 33% IEPOX, 30%

36

|**Species**|**Fractional Contribution**|
|---|---|
|OH|0.07|
|HO2|0.07|
|NO|0.07|
|NO2|0.07|
|Methyl radical (MO2)|0.025|
|Peroxyacetyl radical (ACO3)|0.025|
|HCHO|0.17|
|O3|0.17|
|IEPOX|0.165|
|Isoprene Nitrates|0.15|
|Glyoxal|0.015|



Table 2.5: Species used in the calculation of the mechanism error metric and their corresponding weight.

isoprene nitrates, 30% tetrafunctional isoprene compounds, 2.5% glyoxal, and 4.5% other. Most small isoprene mechanisms exclude tetrafunctional compounds, leaving IEPOX as 50% contribution, 45% isoprene nitrates, and 4.5% glyoxal. As with formaldehyde, each of these are scaled relative to their average maximum concentration. Thus, in our calculations SOA contributes 33% to the total accuracy, with IEPOX contributing 16.5%, isoprene nitrates contributing 15% and glyoxal contributing 1.5%. Isoprene is omitted from the error metric, since its error is represented by the accuracy in the other parameters. Methyl vinyl ketone, methacrolein, peroxyacetyl nitrate, and methyl glyoxal were omitted from accuracy metric due to their relatively lower importance compared to the other species, and their coupling to species already present in the error metric. However, these four species are represented in AMORE-Isoprene, and tables on the performance of each mechanism with respect to these species and all other important species can be found in section S.10. Table 2.5 shows each species and its contribution to the total error metric.

The error metric is calculated by running box model simulations of the Caltech mechanism and the test mechanism in all six conditions, then calculating each individual species error and averaging them using the weights shown in Table 2.5 and then averaging between each of the six conditions to arrive at a single value. The error metric ranges from 0 to 1, with lower values corresponding to less error. This allows for the numerical comparison of various isoprene mechanisms

37

to the Caltech full mechanism.

## **2.2 Results and Discussion**

The final AMORE-Isoprene mechanism consists of 9 species and 22 reactions. A full table of the reactions is shown in Table 2.4. The 9 isoprene species were: isoprene (ISO), isoprene hydroxy peroxy radical (ISOP), isoprene hydroxy peroxide (ISHP), isoprene nitrooxy peroxy radicals (INO2), isoprene hydroxy nitrates (IHN), the lumped species IPC and IPN, isoprene epoxydiol (IEPOX), and lumped multifunctional isoprene nitrates (ISON). IPC and IPN are named based on the reactions they participate in, but they have no true analogues in the full mechanism, as they are used primarily to expand the range of outputs and cycle oxidants and nitrogen oxides. In the following sections, AMORE-Isoprene’s performance will be compared in Box model simulations to the Caltech full mechanism (Section 2.2.1), compared to Chamber data (Section 2.2.2), and compared to the CRACMM-baseline mechanism in CMAQ simulations (Section 2.2.3).

## 2.2.1 Ambient Box Model Simulations

Using F0AM box model simulations and the error metric defined in Section 5.2, we were able to demonstrate the high accuracy of the AMORE-Isoprene mechanism relative to other mechanisms of similar size. Formaldehyde and HO2 were chosen as exemplary species for visual comparison, as they demonstrate the high performance of AMORE-Isoprene relative to other isoprene mechanisms.

Figure 2.4 shows the concentration of HO2 under the six conditions listed in Table 2.3. For HO2, AMORE-Isoprene has stronger agreement with the Caltech full mechanism than the RACM2 isoprene mechanism. In low NO _𝑥_ conditions, the steady state concentration of HO2 was 0.054 ppb for the Caltech full mechanismm, 0.045 ppb for the AMORE-Isoprene mechanism, 0.042 ppb for the CB6r3 mechanism, and 0.026 ppb for the RACM2 mechanism. In high NO _𝑥_ conditions, all mechanisms had similar concentrations of HO2. In high O3 conditions, steady state concentration of HO2 was 0.05 ppb for the Caltech full mechanism, 0.04 ppb for AMORE-Isoprene, 0.04 ppb for

38



<!-- Start of picture text -->
a) Low NO, b) High NO, c) High O3<br>0.06 Fo 0.06 0.06<br>0.05 f, “mens o0s| SY 00s}<br>zoo! = £ _ — B 0.04 #lf poo! ff pe —<br>So03 re PP" rece 0.03} Bee ~0.03 4<br>Z 00 j = 0.02 Z 0.08 G eet<br>i<br>0.01 0.01 0.01 ef<br>000<br>05 10 15 20 0 5 10 15 20 0 5 10 15 20<br>Model Time (h) Model Time (h) Model Time (h)<br>d) High NO, e) High NO, low hv f) Chamber comparison<br>0.03 0.2<br>—8-—Caltech Full<br>0.04 ——CB6r3 0.025) # am ,<br>04 | —4— AMORE 0.15 g ab edimnste<br>a ——Caltech Reduced 2 0.02 2 PP pha<br>—2.0.03 b —8-RACM2 So.o1s | = 0.4 BRfF<br>9a 0.02 b* SC© ool rs)2 a<br>Re k 0.0:<br>0.01 ‘oS 0.005} —_<br>"0 05 1 15 0 5 10 15 20 0 5 10 15 = 20<br>Model Time (h) Model Time (h) Model Time (h)<br><!-- End of picture text -->



<!-- Start of picture text -->
a) Low NO, b) High NO, c) High O,<br>3.5 7. 5<br>B25} Fee, Bs IN a | FF un<br>"0 5 10 15 20 "0 5 10 15 20 "0 5 10 15 20<br>Model Time (h) Model Time (h) Model Time (h)<br>d) High NO, e) High NO, low hv f) Chamber comparison<br>10 ——Caltech Full 10 ~a 25 ym<br>—*—CB6r3 ( Were<br>2 3 —— Caltech Reduced 2 @ 2 kee ~S<br>&cg me [-S-RACM2 Be £ B15) ££ A,<br>5b 4} ay oe 4 o 1°) BF |<br>0 5 10 15 20 0 5 10 15 20 0 5 10 15 20<br>Model Time (h) Model Time (h) Model Time (h)<br><!-- End of picture text -->

Figure 2.6 shows the simulated concentration of the hydroxyl radical under the six conditions listed in Table 3. The AMORE-Isoprene mechanism performs similarly to other highly reduced mechanisms. As with other small mechanisms, AMORE-Isoprene is biased low compared to the full Caltech mechanism. Under low NO _𝑥_ conditions, the AMORE-Isoprene mechanism has near equal behavior to CB6r3 and RACM2 at short time frames and has a more accurate steady state value at longer time frames. At high NO _𝑥_ , the RACM2 mechanism is the most accurate small mechanism, with AMORE-Isoprene having close but slightly lower OH concentrations. At high O3, AMORE-Isoprene has the closest agreement with the Caltech full mechanism. The Caltech Reduced plus mechanism has strong agreement with the full mechanism at all tested conditions, as would be expected. The main reason for the discrepancy in between AMORE-Isoprene and the Caltech full mechanism in hydroxyl radical concentrations is that the Caltech full mechanism has a greater quantity of intermediate species which produce and consume the hydroxyl radical. On balance, this leads to slightly higher hydroxyl radical concentrations, and given that the AMOREIsoprene mechanism is a much smaller mechanism, there are limitations to the extent that this can be corrected. This is further evidenced by the fact that the other small mechanisms have equally low biased hydroxyl radical concentrations. Overall, the AMORE-Isoprene mechanism performs consistently well at predicting OH concentrations, and is in line with similarly sized mechanisms in this regard.

In addition to these plots, a quantitative comparison was made between each of the mechanisms tested based on the overall mechanism error metric defined in Section 5.2. Figure 2.7 shows the mean accuracy of AMORE-Isoprene for a selection of species in each of the six simulation conditions. Lower values correspond to higher accuracy. The AMORE-Isoprene mechanism shows very high accuracy under all conditions, and performed the best under high NO _𝑥_ , high O3, and in comparison to the Chamber data from Paulot et al, which is relatively low NO _𝑥_ , and OH oxidation dominates.

Table 2.6 shows the overall error of each reduced mechanism as defined in Section 5.2 with species weightings described in 2.5. The numerical errors shown in the table represent weighted

41



<!-- Start of picture text -->
a) Low NOx b) High NOx c) High O3<br>4 x10" 2 x10" 4.2 x10<br>ag f, inlet 8 Q 08 apmal<br>08 jiiccengemmmmemmmmonmns & > es<br>fe) 0.0. F [o) 0.5) fo) Pv0. ff<br>"0 5 10 15 20 0 5 10 15 20 "0 5 10 15 20<br>Model Time (hrs) Model Time (hrs) Model Time (hrs)<br>d) High NO3 e) High NOs, low hv f) Chamber comparison<br>x10 2 x10 7 x10<br>sh —-cB6r3 6 gw palette<br>sa : ~*~ AMORE 15 L EE<br>Qa ' —8-RACM Qarom Ss,Q tT iTs a<br>a 6 & —- Caltech Reduced Plus aS _ 5 Ye ae<br>5 5 17<br>i fo)<br>,—EEE 0.5 7<br>"0 5 10 15 2 0 5 10 15 20 "0 5 10 15 20<br>Model Time (hrs) Model Time (hrs) Model Time (hrs)<br><!-- End of picture text -->



<!-- Start of picture text -->
0.60<br>0.50<br>0.40<br>—<br>© 0.30<br>Lu<br>0.20<br>NO, OH HO2 O3 IEPOX Form ISON<br>mLow NO, M®HighNO, MHighNO; SHighNO3;lowhv M®HighO3; mm Chamber<br><!-- End of picture text -->

||**AMORE**|**Caltech Reduced Plus**|**RACM2**|**CB6r3**|
|---|---|---|---|---|
|Species|12|131|9|10|
|Reactions|22|220|12|17|
|Total Error|0.17|0.13|0.44|0.3|
|O3|0.12|0.02|0.15|0.12|
|NO|0.12|0.06|0.22|0.28|
|NO2|0.19|0.08|0.38|0.42|
|HO|0.20|0.17|0.44|0.30|
|HO2|0.29|0.11|0.67|0.29|
|NO3|0.36|0.09|0.47|0.25|
|ISOP|0.14|0.06|0.18|0.11|
|IEPOX|0.17|0.12|0.60|0.27|
|HCHO|0.22|0.11|0.79|0.30|
|MO2|0.53|0.20|0.59|0.56|
|ACO3|0.56|0.27|0.72|0.44|
|PAN|0.53|0.21|0.85|0.52|
|ISOPN|0.43|0.26|0.61|0.77|
|GLY|0.64|0.60|0.86|0.57|
|MGLY|0.63|0.14|0.79|0.23|



Table 2.6: Total Error (individual species error described in Equation 4, species weighting shown in Table 2.5, further discussion in Section 5.2) and mechanism size for four reduced isoprene mechanisms with the Caltech full mechanism as a basis of comparison. Individual species error shown averaged over the six tested conditions.

results validate the AMORE reduction process as a useful method of mechanism reduction, and demonstrate that small mechanisms can retain significant accuracy compared to a much larger reference mechanism.

## 2.2.2 Chamber Box Model Simulations

In order to determine the accuracy of the Caltech full mechanism, which was augmented in this work, Chamber data was used for comparison. The data comes from [61], and contains concentration profiles for isoprene, isoprene hydroxy peroxides (ISHP), and IEPOX. The conditions of the chamber study were replicated using the F0AM box model to determine the accuracy of the Caltech full mechanism and the reduced isoprene mechanisms. As expected, the Caltech Full mechanism matched the concentrations of all measured species from the chamber study.

Figure 2.8 shows the results for IEPOX. The AMORE-Isoprene mechanism is in good qual-

44



<!-- Start of picture text -->
50<br>¢¢® Chamber Data<br>45<br>™=== Caltech<br>40 m= AMORE<br>= RACM2<br>= 35<br>& 30<br>5<br>=& 25 a<br>8 Ry<br>5 20<br>°o<br>15 y<br>10 Ry e y<br>5 ets<br>ett<br>0 0 4 8 12<br>Time (h)<br><!-- End of picture text -->



<!-- Start of picture text -->
a) 2 b) 40<br>—— CRACMM_base 11484 46123 82127 77568 39767 14132 3537 935 263<br>ay ole a] as pan [ ee eee ease nenes o~<br>wu3 44 — nuone 2 0<br>a]3= 8 ov&FI >) |I<br>we 2 8 10<br>: ¢<br>uwg* 2E -10 |<br>4=£<br>oe5-6E 0 Z=3ov -20 801 |<br>= -30 |—— CRACMM base<br>48 165 229 134 79 36 16 13 11 5 —— AMORE<br>-8 -40<br>0 10 20 3.0 40 5.0 60 7.0 8.0 90 100 0 100 200 300 400 500 8&0 700 80 99.0 100.0<br>Binned observed formaldehyde (ppb) Binned observed ozone (ppb)<br><!-- End of picture text -->

bias at low ozone concentrations, because ozone is overpredicted at low concentrations. At higher concentrations, where health implications are presumably more serious, AMORE-Isoprene yielded significantly higher accuracy. AMORE-Isoprene generally tended to increase ozone concentrations by roughly 2-3 ppb for all ozone concentrations. AMORE-Isoprene tends to have higher ozone concentrations and better agreement with the Caltech full mechanism than RACM2 in low NO _𝑥_ box model simulations. Thus, the difference may be attributable a higher prevalence of low NO _𝑥_ conditions.

The CMAQ implementation also included heterogeneous chemistry for IEPOX and first generation isoprene organic nitrates, and deposition for all species. These processes, while not included in our box models, did not significantly impact the overall performance of the mechanism, as OC values were similar between AMORE-Isoprene and the base CRACMM1 mechanism (see section S.16). No significant changes were identified for other observed species such as NO _𝑦_ , and HNO3 (section S.16). The CMAQ model runtime did not increase substantially with AMORE-Isoprene.

We have developed a new reduced isoprene oxidation mechanism for application in largescale atmospheric models, using a novel, semi-automated, graph-theory based approach. Rigorous testing has demonstrated that the AMORE-Isoprene mechanism’s performance is very good for its size, with improved accuracy compared to CB6r3 and RACM2.

A small, accurate isoprene oxidation mechanism would improve the performance of many large-scale models, as we have demonstrated with CMAQ-CRACMM1AMORE simulations, where there was a noticeable improvement in both ozone and formaldehyde bias. In the future we plan additional testing of AMORE-Isoprene in other chemical transport models to characterize the impacts of this mechanism more broadly.

During the algorithmic and manual adjustment process, several useful concepts were developed. First, for a small number of desired measurable outputs, small mechanisms can reach high levels of accuracy if properly structured and optimized. Second, optimization of oxidants and nitrogen oxides, which are highly coupled to the isoprene mechanism, takes precedence over optimization of other species, since inaccuracies in coupled species ultimately propagate to uncoupled

47

species. In addition, the observation that methods reliant on removing aspects of the full mechanism would not work for this application was very important. The path-based approach we have developed to "summarize" the mechanism may be a more sensible starting point for reduction of other atmospheric reaction networks as well.

The AMORE-Isoprene mechanism demonstrates that there is significant potential advantage in the use of algorithms for model reduction. Additional development, informed by the experiences of this study, is underway to more fully automate the model reduction process and further reduce the need for manual adjustments. Future work will extend this work to application to reduction of a wide range of atmospheric chemical mechanisms in addition to the isoprene oxidation mechanism.

CMAQv5.3.3 is available at https://github.com/USEPA/CMAQ and archived at doi: 10.5281/zenodo.5213949. The exact CMAQ code used in this work and CMAQ output is available at doi: 10.23719/1527975.

Code and data for the AMORE algorithm is available at https://github.com/fcw2110/ AMORE_supplementary_files and archived at doi: 10.5281/zenodo.7106505.

All authors contributed to writing the manuscript. Wiser, Sen and McNeill developed the model reduction algorithm. Wiser, Place, Sen, Pye, and McNeill developed the reduced model. Wiser, Place, and Pye performed simulations. CRACMM was conceived by Pye. Research was conceived by Wiser, McNeill, Sen, Westervelt, Henze, and Fiore.

The authors declare no competing interests are present.

This publication was developed under Assistance Agreement No. 84001301 awarded by the U.S. Environmental Protection Agency to McNeill, Westervelt, Henze, and Fiore. The views expressed in this article are those of the authors and do not necessarily represent the views or policies of the U.S. Environmental Protection Agency.

EPA does not endorse any products or commercial services mentioned in this publication.

We would like to thank Dr. Kelvin Bates and Dr. Glenn Wolfe for helpful discussions. We thank Jon Pleim, Ana Torres-Vazquez, and Christine Allen for assistance with CMAQ simulation inputs.

48

This work was supported in part by the U.S. Environmental Protection Agency Office of Research and Development. This research was also supported in part by an appointment to the U.S. Environmental Protection Agency (EPA) Research Participation Program administered by the Oak Ridge Institute for Science and Education (ORISE) through an interagency agreement between the U.S. Department of Energy (DOE) and the U.S. Environmental Protection Agency. ORISE is managed by ORAU under DOE contract number DE-SC0014664. All opinions expressed in this paper are the author’s and do not necessarily reflect the policies and views of US EPA, DOE, or ORAU/ORISE.

49

# **Chapter 3: AMORE 2.0**

## **3.1 Introduction**

In this chapter, we present the Automated Model Reduction version 2.0 (AMORE 2.0) algorithm for the reduction of atmospheric oxidation mechanisms. AMORE is a Python-based tool that has been designed for application to a wide variety of VOC oxidation mechanisms, and has the ability to reduce large mechanisms to desired size while retaining accuracy. Graph theory provides an essential framework for the AMORE 2.0 algorithm. By representing mechanisms as a graph, where species represent vertices and edges represent reactant-product relationships, the algorithm rapidly analyzes and systematically reduces the graph and corresponding mechanism. The algorithm works by measuring and sorting each species by yield from the root species, and then removing species in order of lowest yield by using graph techniques to merge, categorize, reroute, and replace species while maintaining mechanism connectivity and downstream species yields.

There are multiple ways to represent mechanisms as graphs, and in the past, graph theory has been applied to chemical mechanisms beyond model reduction; for example, to identify metastructural properties of the mechanism [84, 85]. In our work, we take the approach of representing species as vertices in the graph, and creating an edge from each pair of reactants and products for each reaction in the mechanism. This methodology has precedent in prior algorithms for mechanism reduction. In 2005, Lu and Law [49] developed the Directed Relation Graph (DRG) method for the reduction of combustion mechanisms. In this method, edges are removed in order from lowest to highest importance, measured as the strength of the edge relative to other edges of the edge species, until the desired mechanism size has been reached. Since then, several variations of this method have been developed [50, 51]. While we draw inspiration from this method and framework, our algorithm takes a distinct approach to mechanism reduction, focusing first and

50

foremost on the removal of vertices (species) rather than edges, which results in higher accuracy at smaller model sizes. Unlike combustion mechanisms, atmospheric oxidation mechanisms are mostly unidirectional with few reversible reactions, usually require reductions upwards of 90% to be used in CTMs, and require that all remaining chemistry be connected to the root species (for example isoprene or camphene). Removing vertices rather than edges is a logical approach to address these constraints, as it makes rerouting of chemical pathways and maintaining connectivity more straightforward, as edges can be rerouted even as vertices are removed.

Prior research has applied reduction methods from other fields to atmospheric chemistry [11, 12, 14], but application of these approaches to large scale model mechanisms have been limited. More recently, algorithms have been developed specifically for the reduction of atmospheric chemical mechanisms. These include the GENOA algorithm [86] and the MechGen reduction scheme [87], as well as our prior work, the AMORE 1.0 algorithm [13]. The AMORE 1.0 algorithm was successful at producing a highly reduced isoprene mechanism that performed well in CTMs. An implementation of the AMORE 1.2 mechanism in the GEOS-Chem chemical transport model showed the potential to reduce chemical solver run times by 25% by incorporating the smaller mechanism while maintaining accuracy compared to the baseline [55]. Implementation of AMORE 1.0 in CMAQ showed reduced formaldehyde bias over the baseline [8]. However, the algorithm was only able to generate mechanisms in a narrow range of sizes and extensive manual optimization was required to refine the mechanism. The AMORE 2.0 algorithm is the first to reduce any atmospheric oxidation mechanism to a desired size both efficiently, requiring only a laptop to reduce very large mechanisms, and accurately without any manual tuning required even after substantial reductions. Our smallest AMORE 2.0 isoprene mechanism greatly outperforms our AMORE 1.0 isoprene mechanism, which itself was already well-suited for use in CTMs. Although the algorithm can reduce mechanisms to any size, there are practical limitations based on desired mechanism accuracy.

In this work, the AMORE 2.0 algorithm is demonstrated on two explicit mechanisms: the Caltech isoprene mechanism [4] and the GECKO-A six-generation camphene mechanism [17]. These

51

mechanisms were selected because they are vastly different in size and development approach, showcasing the versatility of the AMORE 2.0 algorithm.

Isoprene is the second most emitted hydrocarbon after methane, and it oxidizes rapidly, contributing significantly to SOA, ozone, and HO _𝑥_ and NO _𝑥_ cycling [19, 22, 24, 21, 20, 23]. In addition, it is a significant source of atmospheric formaldehyde, an EPA classified air toxic [66]. Thus, an accurate isoprene mechanism must capture its SOA production, formaldehyde production, and impact on ozone, HO _𝑥_ and NO _𝑥_ . Approximately one-third of isoprene SOA can be attributed to isoprene epoxy-diols (IEPOX) [5], with another large portion coming from isoprene tetra-functionals and nitrates. Other small organic species such as glyoxal, acyl-peroxy radical, methacrolein, methyl-vinyl-ketone and peroxyacetyl nitrate (PAN) should also be accounted for.

The Caltech isoprene mechanism is the most recent comprehensive mechanism for the oxidation of isoprene. The mechanism was developed using experimental chamber data and utilizes structure-activity predictions of rate coefficients and product branching ratios (the proportion of a species going to each of its products) to extend available data [88, 89, 63, 62]. With 398 species and 900 reactions, it is on the larger end of manually developed mechanisms. There are several existing reduced mechanisms derived from this mechanism, including the Caltech Reduced Plus and Caltech Mini isoprene mechanisms [5], and the AMORE 1.2 isoprene mechanism [13]. These provide a useful baseline for reduced mechanism performance.

Camphene is an abundant monoterpene that is primarily found in wildfire smoke [35] where it contributes to SOA, but has been less studied [17, 3] than isoprene. Where abundant, Camphene produces formaldehyde and other small organic species and impacts the NO _𝑥_ and HO _𝑥_ budget. In contrast to the Caltech isoprene mechanism, the GECKO-A camphene mechanism was developed algorithmically. The six-generation GECKO-A camphene mechanism contains 103,694 species and 775,070 reactions. The GECKO-A algorithm automatically generates VOC oxidation mechanisms, and utilizes available data and theoretical predictions of product branching ratios and rate constants [36]. Because it is automated, many more species can be included than would be feasible for a manually developed mechanism.

52



<!-- Start of picture text -->
… …<br>… …<br><!-- End of picture text -->

Figure 3.1: Comparison of the full isoprene mechanism graph and an AMORE 2.0 reduced mechanism (15 species) graph for a subset of the mechanism. These graphs show isoprene oxidation via the hydroxyl radical over the first three generations.

## **3.2 Results**

To demonstrate the effectiveness of the AMORE 2.0 algorithm, we generated reduced mechanisms from the Caltech isoprene mechanism and the GECKO-A camphene mechanism. All reduced mechanisms and reference mechanisms are provided in the supporting files.

The Caltech isoprene mechanisms consists of 398 species and 900 reactions [4]. In our prior work, we added reactions to complete degradation pathways for all species in the mechanism. This update, which was used for our reductions, contains 1338 reactions [13]. The AMORE 2.0 algorithm was run on a Dell 2000 MHz Inspiron 15 8-core laptop with 16 GB RAM. The runtime is less than 10 seconds without rate constant optimization and up to 24 minutes with rate constant optimization, which accounted for 99% of the runtime. This step is used to improve select rate constants (see Methods) using gradient descent optimization. This requires repeated measurement of the reduced mechanism yields, leading to longer runtimes. For reduced isoprene mechanisms

53



<!-- Start of picture text -->
0.25<br>0.20<br>0.15<br>0.10<br>0.05<br>0.00<br>0 50 100 150 200 250 300<br>Number of Species<br>AMORE v2.0 Caltech Reduced Plus<br>Caltech Mini AMORE v1.2<br>Mechanism Error<br><!-- End of picture text -->

Figure 3.2: Mechanism error (Equation 8.4) plotted against number of species for several AMORE 2.0 isoprene mechanisms. Error is calculated using equation 8.4 and the Caltech full isoprene mechanism as a reference, and species weightings listed out in section 3.4.2. Three existing reduced isoprene mechanisms are shown as a benchmark: the Caltech reduced plus mechanism (121 species), the Caltech mini isoprene mechanism (92 species), and the AMORE 1.2 mechanism (12 species). Similar sized AMORE mechanisms are highlighted in purple.

with 55 or more species, this rate constant optimization had negligible impact, reducing error by 1% (Equation 8.4) on average. For mechanisms smaller than 55 species, the optimization reduced error by 27% on average, making the added runtime worthwhile.

We conducted several reductions of the isoprene mechanism ranging from 15-300 species (out of 400 in the full mechanism). Figure 3.1 shows a graph visualization of a subset of the full mechanism and the corresponding section of a 15-species reduced mechanism. After generating the mechanisms, we used the F0AM box model [72] to measure their performance. The mechanism error (Equation 8.4) versus mechanism size is shown in Figure 3.2. Here, the error is an aggregate measure of the bias in net yield for several species weighted by priority level over six box model run conditions (Table 5.0.2. Species weights are given in Section S1. Other reduced mechanisms are shown for comparison. The AMORE 2.0 mechanisms outperform existing reduced mechanisms

54

of equal size, improving upon the Caltech Reduced Plus, Caltech Mini, and AMORE 1.2 by 66%, 53% and 67% respectively using our error metric (Equation 8.4).

We assess the performance of the AMORE 2.0 reduced isoprene mechanisms compared to other existing mechanisms for the six highest priority species in the mechanism: OH, HO2, NO, NO2, formaldehyde (HCHO), and IEPOX. We report individual species bias in Δ mol/mol isoprene for a range of conditions. To do this, we obtained atmospheric species concentrations from a global GEOS-Chem run for July 1, 2016. We selected a set of 1000 data points in which the concentration of isoprene was _>_ 0.1 ppb giving a set of box model conditions which replicate the range of conditions expected for isoprene in a CTM. This dataset can be found in the supporting files. We calculated the bias of three AMORE 2.0 mechanisms containing 109, 74, and 15 species, which are compared to the Caltech Reduced Plus, Caltech Mini, and AMORE v1.2 mechanisms respectively. Figure 3.3 shows binned bias in yield (mol/mol isoprene) for each of the reduced mechanism pairs over a 24 hour runtime. Additional box plots with 6, 12, and 200-hour runtimes are provided in Figures S16-S18. All three AMORE 2.0 mechanisms show a substantial reduction in bias over the comparable reduced mechanisms. Different runtimes show no deviation in this comparative trend. Additional concentration plots for other species and box model computational cost (runtime) discussion for these mechanisms are provided in Figures S1-S13 and Section S3 respectively.

The AMORE 2.0 74sp mechanism contains 74 species and 238 reactions, compared to 94 species and 292 reactions in the Caltech Mini mechanism. 39 of the species are represented in both mechanisms. The AMORE 2.0 109sp mechanism has 109 species and 330 reactions, and the Caltech reduced plus mechanism has 121 species and 379 reactions. 68 of the species are represented in both mechanisms. The AMORE 2.0 15sp mechanism has 15 species and 61 reactions and the AMORE v1.2 mechanism has 12 species and 22 reactions. 12 of the species are represented in both mechanisms. The number of species in the reduced mechanism is precisely controlled by the algorithm, whereas the number of reactions are not controlled. We have selected reduced mechanisms with a number of species and reactions comparable to the existing reduced mechanisms.

55



<!-- Start of picture text -->
a)<br>b)<br>c)<br><!-- End of picture text -->

Figure 3.3: Bias (mol/mol isoprene) of the most important species in the isoprene system for 1,000 GEOS-Chem derived atmospheric conditions. Outliers are omitted for visual clarity, the full dataset is available in the supporting files. a) AMORE 2.0 109 sp (109 species, 330 reactions) compared to Caltech reduced plus mechanism (121 species and 379 reactions) b) AMORE 2.0 74 sp (74 species, 238 reactions) compared to Caltech mini mechanism (91 species and 266 reactions) c) AMORE 2.0 15sp (15 species, 61 reactions) compared to AMORE 1.2 mechanism (12 species and 22 reactions).

56

We attribute the improved performance in the AMORE 2.0 mechanisms partly to the inclusion of more reaction generations, specifically the first generation hydroxy allylic radicals from isoprene OH oxidation which are omitted in previously published mechanisms via the steady-state approximation. These radicals are difficult to accurately remove due to their interconnected nature, and thus are prioritized in the AMORE 2.0 algorithm. We also attribute the improved performance to the automatic selection of rate constants and stoichiometric coefficients. Stoichiometric coefficient selection needs to account for many complex removed chemical pathways which is difficult to achieve manually. Rate constants among multiple lumped or categorical species must account for different rate constants among grouped species and average them together. Our method of yield-weighted species merging and rate constant selection would be extremely time-consuming to replicate manually.

The algorithmically generated GECKO-A six-generation camphene mechanism contains 103,694 species and 775,070 reactions, 26,151 of which contribute to SOA production. Our goal with this reduction was to accurately match SOA production using a much smaller mechanism that could feasibly be incorporated into a CTM. To do this, we utilized the categorization method to assign every SOA contributing species to a category (based on vapor pressure and water solubility). We first ran a box model for the mechanism and selected the set of SOA contributing species which accounts for 99% of the SOA concentration, leading to a reduced set of 4,902 species to be categorized. We then used a k-means clustering algorithm to bin the SOA species into a set of categories based on their saturation vapor pressure and Henry’s law constant. This is similar to the Volatility Basis Set used in previous research [90] but is specific to the data available for this mechanism. The resulting set of 15 categories is shown in Figure 3.4. For each category, a new SOA producing category species is created with a vapor pressure and Henry’s law constant equal to the values at the center of the category. As species in each category are removed, their incoming and outgoing connections are rerouted to and from the category species. As SOA producing species are removed, SOA production is maintained by way of the new category species.

We reduced the camphene mechanism to three pre-specified sizes: 177 species, 30 species,

57



<!-- Start of picture text -->
— e<br>3s 7°<br>a ° e@ @ © @,00 © ©<br>oO e @<br>s -5 e@ 25 :. t)<br>v<br>v<br>oO e<br>for os<br>oO e@<br>><br>3-15 .<br>g ° *e °°<br>—20<br>0 5 10 15<br>Logio[Henry's Law Constant (M/atm)]<br><!-- End of picture text -->



<!-- Start of picture text -->
Polluted Continental<br>4| ===™* AMOREGECKO CampheneCamphene 177 ha . ott<br>—<br>_<br>a2=Q = = == AMOREAMORE Camphene Camphene 306 - . wr ae<br>c3 os<br>2.<br>~*<br>© °<br>bs *.<br>= e<br>o2 .<br>Vv . =" 7<br>c bd ——"<br>° * . -<br>w) ? a<br>3S 1 a . .<br>a an a<br>. . .** P<br>0 Pie . —_* =<br>() 5 10 15 20 25<br>Run time (Hours)<br><!-- End of picture text -->



<!-- Start of picture text -->
Continental<br>2.00 7 === GECKO Camphene we<br>= = AMORE Camphene 177 ween<br>_~ 1.75 | == AMORE Camphene 30 wer”<br>ro = = = AMORE Camphene 6 Ad .<br>2 150 o<br>©Ssc 125 e...<br>© :<br>5 100 .<br>5 .: *eet<br>©fo) 0.75 . _—<br>w)—{ 0.50 “Sf.. A —<br>fe) vetoes<br>Y 025 ae an: —_—weer. —_mM<br>0.00<br>() 5 10 15 20 25<br>Run time (Hours)<br><!-- End of picture text -->



<!-- Start of picture text -->
Urban<br>*<br>—~4 :<br>fe} . CVQQGre— — = ms:<br>a : .<br>~—53 . . / = -———_—_ -<br>2 /<br>© .<br>ra)ra :: a /<br>v2 . / y,<br>ra : a<br>° . / J<br><,| : /<br>ol . / —— GECKO Camphene<br>yn e." Z = = AMORE Camphene 177<br>0 ."4 ==== = = AMOREAMORE CampheneCamphene 630<br>() 5 10 15 20 25<br>Run time (Hours)<br><!-- End of picture text -->

## 6-species mechanism converged the most rapidly of all the mechanisms.

Far too many SOA contributing species exist in the full mechanism to be retained in a reduced mechanism. By binning these species into categories, SOA can be accounted for even as the mechanism is significantly reduced. Category species account for 78%, 100% and 100% of SOA in the 177-species, 30-species, and 6-species mechanisms respectively. These categorical species each represent 4,902 removed species. Without this step, a vast majority of SOA production would not be represented in the reduced mechanism, due to the diverse set of species that produce it in the full mechanism. Our novel automated categorization approach alleviates this limitation.

## **3.3 Discussion**

Here we have shown the performance of the algorithm for isoprene and camphene systems. The AMORE 2.0 isoprene mechanisms are able to reduce error compared to existing reduced mechanisms of the same size; accuracy remains high for a wide range of species over a wide range of conditions. The larger AMORE 2.0 reduced camphene mechanisms accurately reproduce SOA production despite being less than 1% of the original size. The runtime of the AMORE 2.0 algorithm is 2 seconds to 32 minutes depending on the original mechanism size and run settings. This fast runtime allows the user to quickly generate many different mechanisms, which can be helpful in optimizing the mechanism size and inputs used. There are many GECKO-A mechanisms with similar or greater complexity than the camphene mechanism studied here. With the AMORE 2.0 algorithm, it would be feasible to reduce any GECKO-A generated mechanism efficiently.

In this work, our mechanism study was limited to box model results. However, we benchmark our isoprene results against other reduced models which have been extensively tested in CTMs, the output of which were compared with ambient observational data. This includes our prior mechanism, the AMORE 1.2 mechanism, which has undergone multiple updates in response to CTM model results [7, 8, 13, 55]. In that work, we observed over-production of NO2 leading to ozone bias. We also observed high formaldehyde production as a result of a diminished number of reaction generations and loss pathways. To account for these issues, we have improved our

60

box model tests to account for the net production of all small inorganic species, including NO2, and have run our bias plots at 24 hours (shown in Figure 3.3), 6 hours, 12 hours, and 200 hours (Figures S16-S18) to account for time-dependent mechanism behavior such as the production of formaldehyde (3.3). We are confident that the improved box model performance of our AMORE 2.0 isoprene model over the AMORE 1.2 mechanism will carry over to CTMs. For camphene, there has yet to be a mechanism applied to a chemical transport model. Here we demonstrate that our reduced models match the full GECKO mechanism reasonably well, and therefore would be useful initial candidate models to run in a CTM which would introduce camphene chemistry to a CTM for the first time.

The AMORE 2.0 algorithm is publicly available for download and is formatted for use in generating new reduced mechanisms. An extensive set of instructions and options is provided in the supporting files. For best results, we recommend creating a set of atmospheric conditions relevant to the mechanism being reduced which can be used to create one representative mechanism or multiple condition-dependent mechanisms. Further discussion of input condition selection is given in section S2. We recommend that the user identify any isomers or closely related species and classify them into groups to be merged throughout the reduction, and to identify any key species to retain in the mechanism. If a group of species must be retained but can be merged, identify one representative species to add to the priority species. The user may also identify categories of species to be represented. This is most appropriate for SOA producing species as a means of maintaining SOA yields through extensive reductions. Here, the user will state a set, or multiple sets, of SOA-producing species, as was done here for camphene. For each category, one representative species will be created, and any removed species will be added to it. The AMORE 2.0 algorithm is computationally efficient, and it would be feasible to do mechanism reduction online for mediumsized mechanisms in response to atmospheric conditions. However, we believe that it would be more effective to create a set of mechanisms offline which represent the broader set of atmospheric conditions. This has the advantage of being more efficient and allowing for error testing prior to incorporation into the model. Furthermore, mechanisms derived from similar conditions will vary

61

minimally, and thus online mechanism reduction would lead to many redundant mechanisms being generated.

Ultimately, the goal of model reduction is to reduce the computational cost of running chemical transport models while maximizing the breadth of the model and minimizing error. This challenge has been approached using other methods, such as solver speedup [43] and training machine learning models to represent subsets of the chemical model [91, 92]. Reduced mechanisms are more interpretable than machine learning models and allow for analysis of specific chemical pathways. Furthermore, they can be used to train machine learning models. We believe that model reduction will play a crucial role in future model runs even as other methods become more developed.

The AMORE 2.0 algorithm has the potential to alleviate a substantial bottleneck in the field of mechanism development, by allowing for the seamless transition from large complex mechanisms to their reduced counterparts. This will not only improve existing reduced mechanisms, but allow for the evaluation of the performance of complex mechanisms via their reduced counterparts in CTMs. By reducing barriers to introducing new mechanisms into CTMs, the AMORE 2.0 algorithm will accelerate the advancement of atmospheric chemistry.

## **3.4 Methods**

## 3.4.1 Algorithm Description

The AMORE 2.0 algorithm is available online through Github and Zenodo as a python script with detailed instructions. The algorithm takes three primary inputs, along with many optional settings. The first input is the mechanism to be reduced. The second input is the desired mechanism size in terms of number of species. The third input is a set of relevant atmospheric conditions for the mechanism. This includes meteorological parameters such as temperature, pressure, and solar intensity. Any meteorological condition needed to calculate the reaction rate constants must be given.

The AMORE 2.0 algorithm begins by calculating the relative rate of reaction for each reaction. This is defined as the rate constant multiplied by the concentration of the secondary reactant, if

62

present. For atmospheric oxidation mechanisms, the second reactant is most often a small inorganic species, whose concentrations must be provided for each condition. These species, such as ozone, HO _𝑥_ , NO _𝑥_ and O2, are best treated as separate from the VOC system because they are universally present in the atmosphere, whereas most species in the mechanism are uniquely derived from the VOC or locally derived from the VOC. This distinction is imperfect, as the abundance of these small molecules is greatly influenced by these VOCs, but it is very useful for graph representation, as they make up the vast majority of secondary reactants. If they are taken out of the graph, representing the mechanism as a graph becomes much simpler. Other secondary reactants are often present, such as organic radicals (RO2). Ideally, concentrations should be given for these species; otherwise the AMORE 2.0 algorithm will assume a low concentration for them. We recommend that these input conditions, including meteorological conditions and species concentrations, be a small representative set of the expected range of conditions, rather than an exhaustive set of all possible conditions. Further discussion of input condition selection is given in section S2.

Other optional inputs to the algorithm include: a list of priority species to be kept in the mechanism, a set of groups of species to be merged together instead of removed, a set of categories in which species can be added to when removed, whether or not to do strongly connected component optimization, and whether or not to reduce the stiffness of the mechanism. A full description of each setting is given in the supporting files.

A weighted directed graph is constructed for the mechanism. The edge weighting connecting a given species A to species B is:



where _𝑒 𝐴𝐵_ is the edge weighting, _𝐴𝑟_ is the set of reactions where _𝐴_ is a reactant, _𝑅𝑟_ is the relative rate of reaction _𝑟_ , and _𝜈𝐵,𝑟_ is the product stoichiometric coefficient of species _𝐵_ in reaction _𝑟_ . Species that are primarily secondary reactants such as HO _𝑥_ , NO _𝑥_ , Ozone, and O2, can only be on the receiving end of an edge to account for their production and consumption.

The strongly connected components (SCC) of the mechanism graph are identified using the

63

## **Algorithm 1** Pseudocode description of the AMORE 2.0 algorithm.

1: function AMORE ( _𝑚𝑒𝑐ℎ𝑎𝑛𝑖𝑠𝑚, 𝑐𝑜𝑛𝑑𝑖𝑡𝑖𝑜𝑛𝑠, 𝑠𝑖𝑧𝑒, 𝑠𝑒𝑡𝑡𝑖𝑛𝑔𝑠_ )

- 2: **for** _𝑥_ ∈ _𝑐𝑜𝑛𝑑𝑖𝑡𝑖𝑜𝑛𝑠_ **do**

3: **for** _𝑟_ ∈ _𝑟𝑒𝑎𝑐𝑡𝑖𝑜𝑛𝑠_ **do** 4: **if** two reactants **then** 5: _𝑥 𝑘𝑟𝑟𝑒𝑙_ =<sup>_𝑥_</sup> _𝑘𝑟_ ∗[2 _𝑛𝑑_ ] 6: **else if** one reactant **then** 7: _𝑥 𝑘𝑟𝑟𝑒𝑙_ =<sup>_𝑥_</sup> _𝑘𝑟_ 8: **for** _𝑛_ ∈ _𝑠𝑝𝑒𝑐𝑖𝑒𝑠_ **do** 9: **for** _𝑟_ ∈ _𝑅𝑛_ = reactions with reactant _𝑛_ **do** 10: **for** _𝑠_ ∈ products of reaction _𝑟_ **do** 11: _𝑒𝑛𝑠_ + = _𝜈𝑟_<sup>_𝑠_∗</sup> <u>�</u> _𝑢𝑅𝑛𝑥 𝑘𝑟𝑟𝑒𝑙𝑥 𝑘𝑢_<sup>_𝑟𝑒𝑙_</sup> 12: _𝑔𝑟𝑎𝑝ℎ𝑥_ = _𝑠𝑒𝑡_ ( _𝑒𝑛𝑚_ ) for all _𝑚_ and _𝑛_ ∈ species

13: graph = mean([ _𝑔𝑟𝑎𝑝ℎ𝑥_ for _𝑥_ in conditions])

14: scc = strongly connected components(graph)

- 15: shortest paths = dijkstra(graph)

16: groups = manual groups + sets of species with identical shortest path classification

- 17: **for** _𝑥_ ∈ _𝑐𝑜𝑛𝑑𝑖𝑡𝑖𝑜𝑛𝑠_ **do**

- 18: _𝑌𝑥_ = rapid yield algorithm( _𝑔𝑟𝑎𝑝ℎ𝑥, 𝑠𝑐𝑐_ )

19: Y = mean([ _𝑌𝑥_ for _𝑥_ in conditions])

- 20: Removal order = sort(Y)

- 21: remaining species = Removal Order [0: len(species)-size]

- 22: **for** _𝑔_ ∈ _𝑔𝑟𝑜𝑢𝑝𝑠_ **do**

23: _𝑒𝑔_ = {}



27: _𝑒𝑔𝑛_ + = _𝑟 𝑗_ ∗ _𝑒 𝑗𝑛_ , _𝑒𝑛𝑔_ + = _𝑒𝑛𝑗_ , _𝑒 𝑗𝑛_ = {} _, 𝑒𝑛𝑗_ = {}

- 28: **for** _𝑐_ ∈ _𝑐𝑎𝑡𝑒𝑔𝑜𝑟𝑖𝑒𝑠_ **do**

- 29: _𝑒𝑐_ = {}, _𝑌𝑐_ =<sup>�</sup> _𝑒𝑛𝑚_ for all species _𝑚_ in _𝑐_ and all species _𝑛_ not in _𝑐_

- 30: **for** _𝑗_ ∈ species in c **do** 31: _𝑟 𝑗_ = _𝑌_<sup>_𝑌_</sup> _𝑐_<sup>_<u>𝑗</u>_</sup>

32: **for** _𝑛_ ∈ species not in _𝑐_ **do**

- 33: _𝑒𝑐𝑛_ + = _𝑟 𝑗_ ∗ _𝑒 𝑗𝑛_ , _𝑒𝑛𝑐_ + = _𝑒𝑛 𝑗_ , _𝑒 𝑗𝑛_ = {} _, 𝑒𝑛𝑗_ = {}

- 34: **for** _𝑛_ ∈ remaining removed species **do**

- 35: **for** _𝑒𝑛𝑘_ ∈ k species **do**

- 36: **for** _𝑒 𝑝𝑛_ ∈ p in species **do**

- 37: _𝑒 𝑝𝑘_ + = _𝑒 𝑝𝑛_ ∗ _𝑒𝑛𝑘_ , _𝑒 𝑝𝑛_ = {} _, 𝑒𝑛𝑐_ = {}

- 38: Rate Constant Optimization, Stiffness Reduction

- 39: **return** Reduced Mechanism

64

SCIPY compressed sparse graph routines (csgraph) module [93]. A SCC is a set of species such that there is a directed path from every species in the SCC to every other species in the SCC. In addition, the shortest path to all species from the root species is identified using Djkistra’s algorithm [94, 93].

The core component of the AMORE 2.0 algorithm is the rapid yield algorithm (RYA), a novel graph theory-based algorithm for the estimation of yields of all species from the root species using the mechanism graph. It is a non-dynamic model that does not use ordinary differential equations and assumes that all reactions proceed to completion.

**Algorithm 2** Pseudocode description of the Rapid Yield algorithm.

1: function Rapid Yield Algorithm( _𝑔𝑟𝑎𝑝ℎ, 𝑠𝑐𝑐, 𝑓_ = _𝑖𝑡𝑒𝑟𝑎𝑡𝑖𝑜𝑛𝑠_ )

2: **for** _𝑐_ ∈ _𝑠𝑐𝑐_ **do** 3: **for** _𝑗_ ∈ species in c **do** 4: _𝑚_ 0 = { _𝑗_ : 1} _, 𝑦_ 0 = { _𝑗_ : 1} 5: **for** _𝑖_ in range(f) **do** 6: _𝑚𝑖_ +1 = {} _, 𝑦_ { _𝑖_ + 1} = _𝑦𝑖_ 7: **for** _𝑛_ ∈ _𝑚𝑖_ **do** 8: **for** _𝑘_ ∈ _𝑠𝑝𝑒𝑐𝑖𝑒𝑠_ **do** 9: _𝑚𝑖_ +1 [ _𝑘_ ]+ = _𝑚𝑖_ [ _𝑛_ ] ∗ _𝑒𝑛𝑘 , 𝑦𝑖_ +1 [ _𝑘_ ]+ = _𝑚𝑖_ [ _𝑛_ ] ∗ _𝑒𝑛𝑘_ 10: **for** _𝑛_ ∈ _𝑌_ **do** _𝑓_ 11: _𝑒_<sup>_𝐷𝐴𝐺_</sup> _𝑗𝑛_ = _𝑦 𝑓_ [ _𝑛_ ] − _𝑠𝑢𝑚_ ( _𝑚 𝑓_ [ _𝑛_ ∈ _𝑐_ ]) ∗( _𝑦 𝑓_ [ _𝑛_ ] − _𝑦 𝑓_ /2 [ _𝑛_ ])/( _𝑠𝑢𝑚_ ( _𝑚 𝑓_ [ _𝑛_ ∈ _𝑐_ ] − _𝑠𝑢𝑚_ ( _𝑚 𝑓_ /2 [ _𝑛_ ∈ _𝑐_ ]) 12: _𝑀_ = { _𝑟𝑜𝑜𝑡_ : 1} _,𝑌_ = { _𝑟𝑜𝑜𝑡_ : 1} 13: **while** _𝑀_ not empty **do** 14: _𝑀𝑛𝑒𝑤_ = {} 15: **for** _𝑛_ ∈ _𝑀_ **do** 16: **for** _𝑘_ ∈ _𝑠𝑝𝑒𝑐𝑖𝑒𝑠_ **do** 17: _𝑌_ [ _𝑘_ ]+ = _𝑒𝑛𝑘_<sup>_𝐷𝐴𝐺_</sup> ∗ _𝑀_ [ _𝑛_ ] _, 𝑀𝑛𝑒𝑤_ [ _𝑘_ ]+ = _𝑒𝑛𝑘_<sup>_𝐷𝐴𝐺_</sup> ∗ _𝑀_ [ _𝑛_ ] 18: _𝑀_ = _𝑀𝑛𝑒𝑤_ 19: **return** Y

The sub-algorithm follows the flow of mass through the graph by assigning a mass of one to the root species and then distributing that mass to products using the edge weightings. This continues through each generation until all of the mechanism mass has reached a product with no outgoing connections. In a directed acyclic graph (DAG), all of the mass will quickly reach a terminal species. The formula describing the yield of a species from the root for a DAG is given here:

65



Where _𝑌𝐴_ is the yield of species _𝐴_ , _𝑁_ is the set of all species, _𝑒𝑛𝐴_ is the edge weighting from species _𝑛_ to species _𝐴_ , and _𝑌𝑛_ is the yield of species _𝑛_ . The species in the graph are topologically ordered [95] and the yield is calculated in that order.

In the case of a cyclic graph, the mass will flow between the species of the SCCs within the graph, repeating infinitely, with smaller amounts of mass remaining through each cycle of the SCCs. However, through linear extrapolation, the final distribution of mass from an SCC can be estimated after a small number of iterations. For each species in a given SCC with an incoming edge from outside of the SCC, the species is assigned a mass of one, and the iterative method is used to determine the acyclic edges from that species. The formula for the acyclic edge connecting SCC species _𝑠_ to outgoing species _𝐴_ is:



Where _𝐶_<sup>_𝑖_thecurrentamountofmassinspecies</sup><sup>_𝐴_atiteration</sup><sup>_𝑖_,</sup><sup>_𝑠𝑐𝑐_representsthesetof</sup> _𝐴_<sup>is</sup> species in the SCC, _𝑌𝐴_<sup>∗</sup><sup>_𝑖_is the total yield of species</sup><sup>_𝐴_at iteration</sup><sup>_𝑖_,</sup><sup>_𝛼𝑖_is the current mass within the</sup> SCC at iteration _𝑖_ over the initial mass within the cycle, _𝑡_ is the final number of iterations, and _𝑌𝐴_<sup>∗</sup> is the final yield of species _𝐴_ assuming all mass has left the SCC. The SCCs can be represented as acyclic edges, and the mechanism graph becomes a direct acyclic graph which follows Equation 4.4.

66

The yields from each condition are averaged together and the species are sorted from lowest to highest average yield. The lowest yield species are removed until the desired number of species in the mechanism is reached. As species are removed, the mechanism graph and the reduced mechanism are updated. Other species characteristics may be taken into account when sorting species. There are three methods of species removal. The first is normal species removal, where the species is removed and incoming connections are rerouted to outgoing connections using the following formula:



where _𝐴_ is the removed species, and _𝑝_ and _𝑐_ are parent and child species of _𝐴_ respectively. As each species is removed, the mechanism graph is updated. Note that when a species is removed, the change in edges in the mechanism is equal to the product of the number of parent and child edges minus the sum of parent and child edges. In order to maximize algorithm efficiency, species whose removal leads to fewer edges are removed first. By removing species in this order, the number of edges in the mechanism never increases as the mechanism is reduced.

The second method of species removal is through grouping species together. Grouping is designed for species which are similar, such as isomers. We have developed an optional subroutine to automatically identify species to be grouped. We identify the shortest path connecting each species to the root using Dijkstra’s algorithm from graph theory. These shortest paths consist of the shortest set of edges traversed from the root species to the species measured. Each edge is assigned a classification based on the reaction types of the reactions involved in the edge. The reaction type is defined by the participating secondary reactant if present; such as OH, HO2, NO, NO2, NO3, O2, O3 or an organic radical; and either photolysis or auto-oxidation otherwise. For example, a two step shortest path for a given species might have the classification { _𝑂𝐻, 𝑁𝑂_ }, indicating a reaction of the root species with OH, followed by the reaction of that product with

67

NO to form the species being measured. Species with identical shortest path classifications are grouped together, as they are assumed to have similar chemical properties. As long as one species in the group remains in the mechanism, referred to as the group lead, a removed species in the group will merge its chemistry with the lead. This means that all instances of that species will be replaced by the lead and the rate constants of the lead will be proportionally adjusted to reflect any new reactions added.







Where _𝑅_<sup>_𝐴_</sup> is the total relative rate of reactions where species _𝐴_ is a reactant, _𝐿_ denotes the group lead species, _𝜇𝑟_ is the current correction factor for reaction _𝑟_ , _𝜌 𝐴_ is the ratio of the yield of species _𝐴_ to the total yield of all species in the group, and _𝜇𝑟_<sup>∗is the updated correction factor for</sup> reaction _𝑟_ .

The final method of species removal is categorization. This is used when a removed species can be put into a bulk category, such as low volatility species. Each category adds a new species and the edges incoming to the removed species will be rerouted to the category. This is useful for groupings of species that are large and might span multiple generations or arise from disparate parts of the mechanism graph. It is different than species grouping, which is reserved for smaller sets of species that are closely related. Categorization has a similar but distinct method from grouping. Rate constants are corrected such that the total rate of reaction of the new category species is the same as the yield-weighted median of the rates of all of the species within the category. The median was chosen because relative rates of a disparate selection of species may span orders of magnitude, and the mean will be biased towards extreme values that are not representative of the bulk category.

68

We observed significant improvement in SOA accuracy for camphene reductions when switching from the yield-weighted mean to the yield-weighted median, as this lead to reduced gas-phase losses and higher SOA production. The multiplier for the rate of a reaction added to the category is given by:







where _𝜌 𝐴_ is the relative yield of removed species _𝐴_ within the category, _𝛿𝑟_ is the sum of products in reaction _𝑟_ which are part of the category, _𝑅𝑚𝑒𝑑𝑖𝑎𝑛_<sup>_𝑐𝑎𝑡_is the yield-weighted median relative</sup> rate of reaction for all reactions within the category, and _𝜇𝑟_<sup>∗istherateconstantmultiplierfor</sup> reaction _𝑟_ . Note that only species connected from outside of the category are considered when calculating the relative yield of a species compared to the category, as shown in Equation 3.8. Any products that are within the category are removed from the reaction to prevent self-edges.

When the species removal is complete, the candidate mechanism is evaluated for SCCs. Any SCCs not involving a category species with species that have been removed are eligible for a rate constant optimization step using gradient descent. When SCCs are reduced, reversible connections are made between species that were not originally connected. In this context, the rate constants of the newly connected species may be imbalanced such that the flow of mass through the reduced SCC is divergent from the mass flow through the original SCC. A rate constant optimization step involving only rate constants of species within the SCC is used, wherein the total mass flow within and out from the reduced SCC is compared to the full SCC using the RYA. The SCC rate constants are optimized using gradient descent to minimize the difference between the reduced and full SCC subsections. We have observed that it takes approximately 100 iterations for the optimization to

69

converge, and the runtime of each iteration is proportional to the size of the SCC and the number of external species it influences. When used, this step accounts for the majority of the algorithm runtime.

After rate constant optimization, any reactions with identical reactants are condensed into one reaction, unless both the reactants and products of the reaction are within the same SCC.

The goal of mechanism reduction is to reduce the computational cost of running the mechanism. One additional aspect of mechanism computational cost is the stiffness of the associated system of differential equations. Higher stiffness occurs from reactions with very fast rates, requiring more steps for the solver. To minimize this problem, we added a stiffness reduction process, which identifies the reactions with the highest relative rates and reduces the rate constants as much as possible without impacting mechanism dynamics. If other reactions occur for that species, either all reactions are adjusted proportionally lower, or none are. Implementing this approach for our isoprene reductions lead to an average reduction in box model simulation time steps of 11% with negligible change in mechanism performance. This stiffness reduction method is an optional step in the reduction.

After this step, the mechanism reduction is complete. The supporting files contains a commented version of the code with a step-by-step guide to running the algorithm with further details on all options and settings.

## 3.4.2 Error Metric

We have developed a testing method for evaluating reduced mechanisms using the F0AM box model. This method involves aggregating error compared to the full mechanism for a set of priority species over a set of important conditions. Our error metric compares the total net production (net yield) of the priority species between the full and reduced mechanism. Our error metric is designed to be bounded between 0 and 1 regardless of the magnitude of the difference between the two output values. This is ideal for adding errors from multiple species over multiple conditions, because it prevents large error from one species from dominating the entire metric. We base our

70

metric off of work from Törnqvist et al. [96], who define a metric using the difference over the arithmetic mean of the two values being compared. We modify this metric slightly to set the bounds of the metric between 0 and 1. The formula for our mechanism error metric is given below:









Here, _𝑥_ is an input condition; _𝑠_ is the measured species; _𝑇_ is the test mechanism; _𝑅_ is the reference mechanism; _𝑝𝑥,𝑠_<sup>_𝑀_(</sup><sup>_𝑡_)and</sup><sup>_𝑐_</sup> _𝑥,𝑠_<sup>_𝑀_(</sup><sup>_𝑡_)are the rate of production and consumption respectively</sup> for species _𝑠_ with input conditions _𝑥_ using mechanism _𝑀_ ; _𝛼𝑠_ denotes whether consumption should be taken into account for species _𝑠_ ; _𝐶𝑥,𝑠_<sup>_𝑀_and</sup><sup>_𝑃_</sup> _𝑥,𝑠_<sup>_𝑀_are the total net consumption and production of</sup> species _𝑠_ with input conditions _𝑥_ for mechanism _𝑇_ over the total run time from _𝑡_ 0 to _𝑡 𝑓_ ; _𝑓𝑥,𝑠_ ( _𝑇, 𝑅_ ) is the performance for an individual species; _𝜔𝑠_ is the weighting for species s; and _𝐹_ ( _𝑇, 𝑅_ ) is the overall mechanism error metric. Each _𝑓_ value ranges from 0 to 1, with 0 indicating perfect matching and 1 indicating infinite divergence. The overall mechanism score function _𝐹_ is also normalized from 0 to 1.

This error metric allows for easy inter-comparison of mechanisms, and was used throughout this work to benchmark algorithm performance. We also apply this error metric to other reduced mechanisms not developed with AMORE in order to see how our methodology compares to other methods. For isoprene, we use the F0AM box model to measure this metric under six different conditions (Table 5.0.2) for the following species: OH, HO2, NO, NO2, O3, formaldehyde, iso-

71

|Run Description|Isop.|OH|HO2|NO|O3|NO3|Photol.|
|---|---|---|---|---|---|---|---|
|High OH|5|0.0002|0.007|0.01|0|0|1|
|High OH & NO|5|0.0002|0.007|0.2|0|0|0|
|High O3|2|0.00001|0.007|0.01|100|0|1|
|High NO3|1|0.00001|0.007|0.1|0|0.0002|1|
|High NO3no_ℎ𝜈_|1|0.00001|0.007|0.1|0|0.0002|0|
|High Isop|10|0.0002|0.007|0.02|0|0|1|



Table 3.1: Six different run conditions used to evaluate mechanisms. All species values have units of ppb. Photolysis is a unitless constant.

prene, IEPOX, methylglyoxal, gyloxal, acyl-peroxy radical, methyl radical, methacrolein, methyl vinyl ketone, isoprene tetrafunctional compounds, isoprene hydroxy nitrates, and isoprene nitrates excluding hydroxy nitrates. We do not measure peroxy-acetyl nitrate directly, as it is produced via the reaction of NO2 and the acyl-peroxy radical, both of which we account for. The result of this calculation is shown in Figure 3.2 for several reduced isoprene mechanisms and gives a measure of overall mechanism performance averaged for these species under the selected conditions.

72

# **Chapter 4: Rapid Yield Algorithm**

The graph theory is a useful framework for the representation and analysis of chemical mechanisms. One key insight that we have developed using this framework is that the yields of all species in a mechanism can be determined for a given set of input conditions without the use of an ordinary differential equation (ODE) solver using a graph theoretical approach. This method, which we call the Rapid Yield Algorithm (RYA), is an essential component of the AMORE 2.0 algorithm, and was also used in the AMORE 1.0 algorithm, GA-AMORE algorithm, and AMORE Gradient Descent. It has potential applications outside of the AMORE project umbrella as well.

In chemistry, the yield is defined as the amount of product obtained from a given reaction or set of reactions. The yield is time independent, as it is generally measured when the set of reactions has gone to completion. The yield of a product is well defined in the context of a closed system where the product undergoes no further reactions and there is no mass transfer outside of the system.

However, this definition can be extended to represent the total amount of mass that has passed through a given species during the progression of the chemical reactions. For example, imagine a simple reaction network: _𝐴_ → _𝐵_ , _𝐵_ → _𝐶_ . In this simple scheme, species A reacts to form species B which reacts to form species C. When all reactions have gone to completion, all of the mass will be in species C, leading to a yield of 100%. However, all of the mass will have passed through both species A and species B. In our modified yield definition, these species also have yields of 100%. This definition is less useful for determining what the final state of the system is, but it is far more useful when trying to determine how important a particular mechanistic pathway is to the mechanism.

The yield, as defined above, can be determined from a chemical mechanism using straightforward graph theoretical techniques. This calculation can be done with varying levels of complexity and error depending on qualities of the mechanism itself and the boundary of the system.

73

In this chapter, we first detail the method of representing mechanisms as graphs, and then detail the methodology of the RYA for mechanisms of varying levels of complexity. Finally, we discuss limitations and applications of the method.

## **4.1 Mechanisms as Graphs**

There are multiple methods of representing a mechanism as a graph. For our work, every species in the mechanism is represented uniquely by one vertex. Edges are created by parsing every reaction and creating an edge going from each reactant to each product. No duplicate edges are created.

This method of graph representation loses some fidelity in representing the full mechanism. For example, any instance in which there are multiple products or reactants leads to the creation of multiple edges from one reaction, with no method of tracing the edges back to the original reaction. In addition, if the same reactant/product pair appears in multiple reactions, each of these instances will be condensed into one edge. To counteract these limitations, we employ a combination of system-specific assumptions and graph object modifications to include more information about the mechanism system in the graph representation. We will demonstrate this using sample mechanisms with higher and higher degrees of complexity.

The simplest mechanism is one in which each reaction contains just one product and one reactant. Figure 4.1.a shows a sample mechanism and its corresponding graph. In this context, the graph representation captures the mechanism in high fidelity. Each edge represents one reaction. However, in order to fully capture the mechanism behavior, we have to incorporate the relative ratio of the two products B and C. To do this, we add a weighting to the edges, which represents number of moles per mol of A going to both B and C respectively, assuming the two reactions occur in tandem competing with each other.

A more complex mechanism might span more generations, while still having only one reactant and product per reaction. The sample mechanism and corresponding graph are shown in Figure 4.1.b.

74



<!-- Start of picture text -->
A  →  B, k = 0.7 0.5 D<br>0.7 B A  →  C, k = 0.3 0.7 B<br>B  →  D, k = 0.25<br>A A  →→  B, k = 0.7 C, k = 0.3 A B C  →→  E, k = 0.25 F, k = 0.8 A 0.5 E 1.0<br>0.3 C F  →  G, k = 1 0.3 C G<br>E  →  G, k = 0.5 1.0 F 1.0<br>a) b)<br>A + OH →  0.6 B + 0.4 C, k = 0.7<br>0.1 D A + NO →  0.8 C, k = 0.3 0.66 D<br>A A  →→  0.6 B + 0.4 C, k = 0.7 0.8 C, k = 0.3 0.42 B B + B + NOOH →→  D, k = 0.25  E, k = 0.25 0.32 B<br>B C  →→  0.1 D + 0.9 E, k = 0.25 0.6 F, k = 0.8 A 0.9 E 0.4 C + F  → OH 0.8 G, k = 1 →  0.6 F, k = 0.8 A 0.33 E 0.4<br>F  →  0.8 G, k = 1 0.52 G E + OH →  0.4 G, k = 0.5 0.58 G<br>E  →  0.4 G, k = 0.5 C C<br>0.6 F 0.8 [OH] = 0.1 0.6 F 0.8<br>c) d) [NO] = 0.2<br><!-- End of picture text -->

Figure 4.1: Simple mechanisms and their graph representation.

For a mechanism in which a reaction might have multiple products, there is no longer a oneto-one correspondence between reactions. The edge weightings must now account for not only the distribution of species based off of competing rate constants, but also based off of stoichiometric coefficients as well. Figure 4.1.c shows a sample mechanism and its corresponding graph.

From this, we derive a formula for the edge weighting between two species:



With the introduction of multiple reactants, the mechanism graph loses substantial fidelity. For each reactant, there must be an edge connecting to each of the products. This not only separates the reaction into multiple edges, but decouples the two reactants, which are normally co-dependent for the progression of the reaction. In our prior sample mechanisms, the ratio of products was a constant value which was fully represented by the mechanism graph. The concentration of the lone reactant only impacts the rate of reaction, not the distribution of products. However, in the context of two reactants, the distribution of products is not a static value, as it is dependent on the concentration of both reactants and the extent to which they overlap.

Given this, two reactant mechanisms are difficult to appropriately represent using this method. However, one unique feature of atmospheric oxidation mechanisms is that the second reactants

75

are dominated by a small set of inorganic species, and the remaining second reactants are easily categorized. These inorganic species include OH, HO2, O3, NO, NO2, NO3, and various organic radicals. The benefit of this pattern is that the variety of second reactants is so minimal that we can integrate them into our graph object rather than incorporating them into the graph structure. Furthermore, if we provide reasonable concentrations for these species (or multiple for multiple graphs), we can again assume constant distribution of products regardless of the concentration of primary reactant. The mechanism is re-written without these second reactants in the mechanism, and in place of the original rate constants, we use the rate constant multiplied by the provided concentration for the second reactant. This product is referred to as the relative rate, defined here:



This product of the concentration and rate constant represents the relative rate of the reaction compared to other reactions involving the same primary reactant. Thus, while the primary reactant concentration will impact the rate of all of its reactions, the ratio of those rates will remain the same under constant concentrations of those secondary reactants. Using the relative rates, we can modify Equation 4.1 as:



Thus, given a set of secondary reactants with concentrations provided, we can use the same mechanism graph representation. This is demonstrated for a sample mechanism with species OH and NO as secondary reactants in Figure 4.1.d.

For any mechanism with reactant combinations that cannot be easily typified, this graph framework is less useful. However, for atmospheric oxidation mechanisms, this framework is very useful.

76

## **4.2 Rapid Yield Algorithm**

The Rapid Yield Algorithm is an algorithm for the prediction of yields of all species in the mechanism without the use of an ODE solver. In order to use the RYA, a mechanism must only contain reactions with either one reactant, or secondary reactants which may be assigned a representative concentration. In theory, this applies to any mechanism with the caveat that assigning constant concentrations to species results in loss of accuracy, but is most applicable where most or all of secondary reactant concentrations are not expected to change significantly throughout the runtime. When conducting mechanism reduction, this requirement of constant conditions becomes a benefit, as it allows the reduction algorithm to measure the importance of each mechanistic pathway in a way that is disentangled from the time-dependent nature of the mechanism.

The RYA traces the flow of mass through the mechanism graph. If we assume that every reaction in the mechanism will proceed to completion, then, given a set of starting concentrations, the mass will proceed through the mechanism until the only species with remaining mass have no reactions in which they are a reactant (or there is a cyclical reaction at the end of the mechanism). We define the yield of a given species as the amount of mass that has passed through it. This can be taken as a fraction of the original starting mass, or as an amount. These yields can be calculated for every species without the use of ordinary differential equations using the mechanism graph.

For a directed acyclic graph (DAG), this calculation is straightforward. All mechanism graphs are directed, as the edge goes from the direction of the reactant to the product. An acyclic graph is one such that there is no pair of species such that the first species can be reached from the second and the second can be reach from the first. In other words, there are no closed loops in a directed acyclic graph.

The RYA is an iterative algorithm. Starting with a species with non-zero mass, in the first step the species is assumed to react fully to form all of its products in proportion to its original mass and the edge weightings of its products. In the subsequent step, the mass of those products is distributed to their products in proportion to their edge weightings. The same process of distributing mass is

77



<!-- Start of picture text -->
0.35<br>0.7 0.7<br>A  →  B, k = 0.7 0.5 D<br>0.7 B A  →  C, k = 0.3 0.7 B<br>1 B  →  D, k = 0.25 1 0.35<br>A A  →→  B, k = 0.7 C, k = 0.3 A 0.3 B C  →→  E, k = 0.25 F, k = 0.8 A 0.3 0.5 E 1.0 0.65<br>0.3 F  →  G, k = 1 0.3 0.3 G<br>C E  →  G, k = 0.5 C<br>1.0 F 1.0<br>a) b)<br>0.042 A + OH →  0.6 B + 0.4 C, k = 0.7 0.21<br>0.42 0.1 D A + NO →  0.8 C, k = 0.3 0.32 0.66 D<br>A  →  0.6 B + 0.4 C, k = 0.7 B B + NO →  D, k = 0.25  B<br>A  →  0.8 C, k = 0.3 1 0.42 0.378 B + OH →  E, k = 0.25 1 0.32 0.106<br>B C  →→  0.1 D + 0.9 E, k = 0.25 0.6 F, k = 0.8 A 0.9 E 0.4 0.4 C + F  → OH 0.8 G, k = 1 →  0.6 F, k = 0.8 A 0.33 E 0.4 0.32<br>F  →  0.8 G, k = 1 0.52 0.52 0.312 G E + OH →  0.4 G, k = 0.5 0.58 0.58 0.348 G<br>E  →  0.4 G, k = 0.5 C C<br>0.6 F 0.8 [OH] = 0.1 0.6 F 0.8<br>c) d) [NO] = 0.2<br><!-- End of picture text -->

Figure 4.2: Simple mechanisms with their graph representation and yields of all species listed above each species.

repeated until all of the mass has reached species without outgoing edges.

The formula for the yield of a given species is as follows:



Here, _𝑌𝐴_ is the yield of species A, N is the set of species in the mechanism, and _𝑒𝑛 𝐴_ is the edge weighting as defined in equation 4.3. Note that this formula requires the calculation of the _𝑌𝑛_ for any species containing an edge connecting to species A. Thus, this same yield calculation for those species must precede the yield calculation of species A. For a directed acyclic graph, this is easily accomplished by ordering the species such that the incoming edges (parents) of a species precede it in the ordering, and that this is true for all species. This ordering is referred to as a topological ordering [95], and is a common sorting method for directed acyclic graphs.

Figure 4.2 shows the mechanisms, graphs, and species yields of the four sample mechanisms.

This method does not apply to cyclic graphs where more advanced tools must be used. In a cyclic graph, there are loops within the graph such that starting from a given species there exists a path to return back to that species. A set of species that all can be mutually reached from each other is called a strongly connected component (SCC). In a cyclic graph, there is no topological

78

ordering, as species within a strongly connected component have no hierarchy and thus cannot be ordered such that all parent species precede child species. Given this, equation 4.3 cannot be applied as it requires that the species be topologically ordered.

As mass flows through a SCC, it will shuttle between the species of the SCC back and forth, while simultaneously losing mass to the outside system via edges to species outside of the SCC. As long as the SCC has one outgoing edge, all of the mass will eventually leave the SCC, and the distribution of products from the SCC is a non-dynamic quantity. That is, the distribution of products from the SCC is uniquely determined by the initial concentration of the species in the SCC, so long as the conditions for the RYA are met.

An iterative method can be used to determine what the distribution of products arising from the SCC is. To do this, an initial mass is assigned to the species of the SCC. Then, as with the standard RYA step, mass is distributed to all products of those species according to the edge weightings. Whereas mass will never return to a species in a DAG, it will return to a species in a SCC. As the mass continues to be distributed among the products, mass will bounce around within the SCC and also leave the SCC. The final product distribution is the yield of products when the total mass within the SCC is zero. This final product distribution is represented by the following equation:



Where _𝐶_<sup>_𝑖_thecurrentamountofmassinspeciesAatiteration</sup><sup>_𝑖_,sccrepresentsthesetof</sup> _𝐴_<sup>is</sup> species in the SCC, _𝑌𝐴_<sup>∗</sup><sup>_𝑖_isthetotalyieldofspeciesAatiterationi,and</sup><sup>_𝑌_</sup> _𝐴_<sup>∗isthefinalyieldof</sup> species A assuming all mass has left the SCC.

However, SCCs often consist of very rapid reactions between species in the SCC and very slow outgoing reactions, as is the case with reversible organic radical forming reactions. One such

79

example is the first few generations of isoprene oxidation by OH, which contains a large SCC connecting to the subsequent stages of the mechanism.

Given the capacity for SCCs to oscillate rapidly, the amount of mass lost from the SCC on a given iteration may be relatively small. If 1% of the mass is lost from the SCC at every step, then it would take 458 steps for 1% of the mass to be remaining. Using this many steps to determine the final product distribution of an SCC is inefficient and also not necessary.

In the first steps, more outgoing mass will have gone to products closer to the source species. However, after some number of steps, the mass within the SCC will have traversed the SCC multiple times, and mass will have been able to exit the SCC from every possible outgoing edge. At this stage, the ratio of products will not change significantly. The final distribution of products can then be determined by taking two measurements of the product distribution at two predetermined number of steps.

The number of steps must be selected such that the mass has cycled through the SCC multiple times at the first measurement (once at minimum), and again at the second measurement. In an SCC with _𝑁_ species, it will take at most 2 _𝑁_ steps to return to starting species _𝐴_ (traversing out N steps and back N steps). Thus we recommend taking the distribution measurement at _>_ 2 _𝑁_ steps and _>_ 4 _𝑁_ steps to ensure the mass has been well distributed to all possible products.

With these measurements, linear extrapolation can be used to predict the final mass of the products, given that the ratio of products remains the same between the two measurements, and the final total yield of all products is inversely proportional to the amount of mass remaining in the SCC at the current step. The following formula gives the product yield from an SCC using this method:



80

Where _𝛼_<sup>_𝑖_</sup> is the current mass within the SCC at iteration _𝑖_ over the initial mass within the cycle, t is the final number of iterations, and _𝑌𝐴_<sup>∗is the final yield of species A assuming all mass has left</sup> the SCC. These SCC specific yields are used to craft new directed acyclic edges. Thus, for every SCC in the mechanism, any species in the SCC with a parent outside of the SCC will receive a new set of edges connecting to all species that are children of species in the SCC (but not in the SCC themselves). All other edges involving SCC species are removed. This process converts the entire graph to a DAG and the mechanism graph becomes a direct acyclic graph which follows Equation 4.4.

Using this method, the products of an SCC can be determined using roughly 4 _𝑁_ steps. Given that the size of most SCCs encountered in atmospheric oxidation mechanisms are less than 20, and the majority of which are equal to 2, this is a very minimal requirement for accurate SCC product prediction.

The accuracy of this method can be demonstrated on the isoprene mechanism. Figure 4.3 shows the yield of all species in the isoprene mechanism under six different conditions as predicted by the RYA compared to the box model. The prediction is nearly identical to the box model measurement, with some slight deviation for some species, which we attribute to reactions involving two organic reactants whose concentrations are not well-approximated as constants.

The benefit of the RYA is in its efficiency at calculating yields compared to box models, which allows for optimization and mechanism reduction methods that would be otherwise computationally costly. In our system, the RYA is approximately 6 times faster than the corresponding box model.

## **4.3 Time-Dependent Yields**

The RYA has two key limitations. The first is that the yields are given assuming that all reactions have gone to completion, which implies _𝑡_ = ∞. The second is that reactions with two reactants must assume a constant concentration for the second reactant, even if it is better modeled as a dynamic quantity. Luckily, there are workarounds for both of these issues, which can improve

81



Figure 4.3: Comparison of the Rapid Yield Algorithm to a box model for all species in the isoprene mechanism under six different conditions.

82

the performance of the algorithm.

The assumption that all reactions have gone to completion is generally not valid in the atmosphere. Atmospheric VOC oxidation does not take place in a closed system. In the atmosphere, species are transported to different locations, or are lost to particle forming processes. This means that the chemistry generally will not have time to proceed to completion. As a result, the estimated yields given by the RYA will be an overestimate, since these loss processes are not factored in. This issue is particularly acute for slow timescale reactions and for multi-generation mechanistic pathways.

For example, we have observed that formaldehyde yields in the isoprene mechanism are much higher in a box model over long runtimes compared to short runtimes, due to slow timescale reactions. This has lead to a tendency for formaldehyde to be overestimated in reduced mechanisms, due to the fact that the _𝑡_ = ∞ yield was used as the reference value, and multiple generations of chemistry were reduced to one or two fast generations, leading to immediate production of formaldehyde. Much of that formaldehyde yield comes from highly functionalized species with long lifetimes that are lost to transport or particle formation in chemical transport models.

There are two workarounds to address this issue in the RYA. The first is to incorporate any non-gas phase or non-chemical loss processes into the mechanism using representative chemical reactions. Secondary organic aerosol (particle) formation is able to be represented as a chemical reaction and heterogeneous (which include the gas and particle phase) mechanisms do exist for some species. For example, the GECKO-A model has built in heterogeneous chemistry, making SOA yields easy to incorporate into the RYA and related algorithms. There is currently no way to represent transport loss in a chemical mechanism, yet there is no theoretical limitation to its inclusion for the purpose of proper yield calibration.

The second workaround is to incorporate timescales into the RYA itself. The relative rate of every reaction (Equation 4.2) gives the rate of reaction per unit concentration of the reacting species. The rate of consumption _𝑘 𝑠_ of species _𝑠_ at concentration [ _𝑠_ ] will be:

83



where _𝑅𝑠_ is the set of reactions where _𝑠_ is a reactant and _𝑘𝑟𝑒𝑙_<sup>_𝑟_is the relative rate of reaction</sup><sup>_𝑟_,</sup> and _𝑘_<sup>_𝑠_Assuming an initial starting concentration[</sup><sup>_𝑠_]0</sup> _𝑟𝑒𝑙_<sup>is the relative rate of reaction of species</sup><sup>_𝑠_.</sup> and no additional sources of _𝑠_ , the time-dependent concentration [ _𝑠_ ]( _𝑡_ ) is given by:



The fraction of the initial [ _𝑠_ ] consumed is given by:



This fraction represents the proportion of _𝑠_ that has been consumed. This proportion can be used as an adjustment factor for the calculation of graph edges:



where _𝑒𝑛𝑚_ ( _𝑡_ ) is the modified time-dependent edge between species _𝑛_ and species _𝑚_ . Using this modified version of Equation 4.3, the time-dependent yield of any species can be predicted without the use of an ordinary differential equation. We note that while the RYA is theoretically accurate as long as the core assumptions hold, this time-dependent methodology is an approximation that is not predicted to be precisely accurate. Figure 4.4 shows the concentration predictions by the time-dependent RYA of formaldehyde, trans-IEPOX and HMML under three different conditions compared to a box model ODE solver. These species were selected because they have different responses to the input conditions and production time-scales. The time-dependent RYA tends to be shifted early compared to the box model, but the difference is minimal for formaldehyde and trans-IEPOX while being more significant for HMML.

This methodology allows for a time-dependent prediction of species concentrations without the

84



<!-- Start of picture text -->
Formaldehyde IEPOXt HMML<br>1.0 0.06 0.05<br>0.8 0.04<br>0.04<br>0.6 0.03<br>0.4 0.02<br>0.02<br>0.2 0.01<br>0.0 0 0<br>0 2 4 6 8 10 12 0 2 4 6 8 10 12 0 2 4 6 8 10 12<br>Time (Hours) Time (Hours) Time (Hours)<br>a) Rapid Yield Algorithm Box Model b) IEPOX Test IEPOX Ref c) HMML Test HMML Ref<br>Formaldehyde IEPOXt HMML<br>1.2 0.02 0.08<br>1<br>0.015 0.06<br>0.8<br>0.6 0.01 0.04<br>0.4<br>0.005 0.02<br>0.2<br>0 0 0<br>0 2 4 6 8 10 12 0 2 4 6 8 10 12 0 2 4 6 8 10 12<br>Time (Hours) Time (Hours) Time (Hours)<br>d) Rapid Yield Algorithm Box Model e) Rapid Yield Algorithm Box Model f) Rapid Yield Algorithm Box Model<br>Formaldehyde IEPOXt HMML<br>0.8 0.02 0.03<br>0.025<br>0.6 0.015<br>0.02<br>0.4 0.01 0.015<br>0.01<br>0.2 0.005<br>0.005<br>0.0 0 0<br>0 2 4 6 8 10 12 0 2 4 6 8 10 12 0 2 4 6 8 10 12<br>Time (Hours) Time (Hours) Time (Hours)<br>g) Rapid Yield Algorithm Box Model h) Rapid Yield Algorithm Box Model i) Rapid Yield Algorithm Box Model<br>Concentration (ppb) Concentration (ppb) Concentration (ppb)<br>Concentration  (ppb) Concentration (ppb) Concentration (ppb)<br>Concentration (ppb) Concentration (ppb) Concentration (ppb)<br><!-- End of picture text -->

Figure 4.4: Comparison of the time-dependent Algorithm and the F0AM box model for formaldehyde (a,d,g), trans-IEPOX (b,e,h), and HMML (c,f,i) under the high OH (a,b,c), high OH and NO (d,e,f), and high NO3 low hv (g,h,i) conditions from Table 5.0.2, with the isoprene concentration set to 1 pbb for each condition.

85

use of an ODE. Because there is no ODE, the RYA method can calculate the concentration at each time independently, meaning that the concentration only needs to be calculated for the desired time (as opposed to multiple time-stamps).

The benefit of this approach is in speeding up the chemistry solver. The F0AM box model in MATLAB requires roughly 0.65 seconds to run the full isoprene mechanism under one input condition. Comparatively, the RYA takes approximately 0.11 seconds per condition after the graph processing has been completed, which takes 0.5 seconds, but would not need to be repeated each time. This is an approximately 6x speed up over the ODE solver, with the caveat that only one timestamp can be chosen to be measured at a time. Additionally, the improvement may be increased by further optimization of the code beyond what was done for this work. While this method is not fully accurate, it does demonstrate the possibility of an ODE-free chemical solver based in graph theory, and there is significant room for refinement of this method.

## **4.4 Asynchronous Reactants**

Another limitation of the RYA is the time-dependent asynchronicity between reactants. The core assumption of the RYA is that all secondary reactants can be assigned a constant concentration to calculate the relative rates of reaction. Multiple concentrations can be provided and calculated separately then averaged out. This assumption works generally well for mechanism reduction, where any minor inconsistencies in species yield predictions are buffered by the fact that the reduction process is a principled reduction of the full mechanism. That is to say, to the extent this assumption does not hold, the impact on the final reduced mechanism is minimal.

However, if the goal is to accurately predict yields of species from the mechanism, assumption of constant concentration for secondary reactants is not always valid. This is particularly true for reactions in which both reactants are derived uniquely from the source species, and thus there is no clear hierarchy in terms of which species is the primary and secondary reactant. For example, consider the two reactions, ISOP1OH2OO + HO2, and ISOP1OH2OO + ISOP3OH4OO. In the first reaction, ISOP1OH2OO is the clear primary reactant, as HO2 is a small inorganic species which is

86

prominent throughout the atmosphere, and can be considered a background species, even though its concentration is time-dependent. In the second reaction, there is no clear primary reactant, as both species are isomers of each other, and are derived from the same root species (isoprene). In this case, we can assign a concentration for one of the species, ISOP3OH4OO for example, but we will most likely misrepresent the true ratio of the rates of the first and second reactions, which are competing with each other. This is because the concentration of ISOP3OH4OO is inherently time-dependent as it is uniquely derived from isoprene, and its concentration is governed by the rate of the reactions that proceed it.

Although we do not have a general solution to this problem, we have developed a preliminary approach to try to reduce error in this context. We will use the following mechanism as an example:



<!-- Start of picture text -->
k3 D<br>B<br>0.5<br>A  →  0.5 B + 0.5 C, k = 1<br>C  →  E, k1 A k2<br>F<br>B  →  D, k3 0.5<br>B + E  →  F, k2 C k1<br>E<br><!-- End of picture text -->

Figure 4.5: Toy model mechanism for the prediction of end products D and F given asynchronous reactants B and E.

This mechanism contains a simple version of the asynchronous reactant problem. Species _𝐵_ and _𝐶_ are derived from _𝐴_ in even proportion. _𝐶_ then forms _𝐸_ at rate _𝑘_ 1, and _𝐵_ can form _𝐷_ at rate _𝑘_ 3 or _𝐹_ by reacting with E at rate _𝑘_ 2. The ratio of end concentrations of species _𝐹_ and _𝐷_ , termed here<sup>_<u>𝐹</u>_willbedeterminedbytherateconstants</sup><sup>_𝑘_1,</sup><sup>_𝑘_2,and</sup><sup>_𝑘_3,andtheinitialconcentrationof</sup> _𝐷_<sup>,</sup> species _𝐴_ , as these are the only free parameters in the system. The upper bound on _𝐷_<sup>_<u>𝐹</u>_is given by:</sup>



This upper bound assumes that all of species _𝐸_ is produced quickly and is immediately avail-

87

able to react with species _𝐶_ . However, this upper bound is unlikely to be achieved, as the reduction in concentration [ _𝐸_ ] over time will reduce its rate relative to the other reaction which only depends on [ _𝐵_ ]. In order for _𝐷_<sup>_<u>𝐹</u>_to be near its upper bound, the production of</sup><sup>_𝐸_from</sup><sup>_𝐶_must be faster than</sup> the production of _𝐷_ from _𝐵_ . Thus, _𝑘_ 1 _>> 𝑘_ 3 must hold.

The lower bound of _𝐹_ / _𝐷_ is 0. This is the case when _𝑘_ 1 is so small that effectively no _𝐸_ is able to react with _𝐵_ , leading to the production of _𝐷_ only. Thus, to reach the lower bound, _𝑘_ 1 _<< 𝑘_ 3 must hold.

We expect _𝐷_<sup>_<u>𝐹</u>_to increase slowly near the upper and lower bounds and rapidly at the transition</sup> point where the reaction _𝐵_ + _𝐸_ → _𝐹_ becomes competitive with _𝐵_ → _𝐷_ .

Given these bounds and expected behavior, we propose a basic equation for the prediction of _<u>𝐹</u>_ /<sup>_𝐷_with two modifiable parameters</sup><sup>_𝛼_1 and</sup><sup>_𝛼_2:</sup>



The parameter _𝛼_ 2 represents the deviation of the maximum of _𝐷_<sup>_<u>𝐹</u>_from the upper bound, and is</sup> always between 0 and 1. The second term in the equation, in parenthesis, represents the proposed relationship between _𝐷_<sup>_<u>𝐹</u>_and the ratio of</sup><sup>_𝑘_1 and</sup><sup>_𝑘_3.</sup><sup>_𝛼_2 is an adjustment factor on that ratio.</sup>

We have tested this proposed function for _𝐷_<sup>_<u>𝐹</u>_usingtheF0AMboxmodel.Figure4.6shows</sup> Equation 4.12 plotted against the log10 of _𝑘_ 1, compared to empirically derived values of _𝐷_<sup>_<u>𝐹</u>_using</sup> the F0AM box model. In this run, _𝑘_ 3 = 1 _𝑠_<sup>−1</sup> , _𝑘_ 2 = 5 ∗ 10<sup>−8</sup> _𝑀_<sup>−1</sup> _𝑠_<sup>−1</sup> , [ _𝐴_ ]0 = 1 ppb, _𝛼_ 1 = 0 _._ 0276, and _𝛼_ 2 = 0 _._ 1.

The proposed function for _𝐷_<sup>_<u>𝐹</u>_closely matches the measured values of</sup> _𝐷_<sup>_<u>𝐹</u>_given well chosen val-</sup> ues for _𝛼_ 1 and _𝛼_ 2. This shows the potential to account for asynchronous reactants within the graph theory framework, potentially extending the utility of this method. At this stage, we do not know how well this methodology extends to larger mechanisms, and whether or not the tunable _𝛼_ parameters must be found for each individual system. Further work is needed to explore the possibilities and limitations of this approach, but here we demonstrate that it is theoretically possible to account for asynchronous reactants without the use of a time-dependent ODE solver.

88



<!-- Start of picture text -->
20<br>15<br>10<br>5<br>-5 0 5<br>log(k1)<br>F/D<br><!-- End of picture text -->

Figure 4.6: The ratio of end time concentrations of species _𝐹_ and species _𝐷_ versus log10( _𝑘_ 1) from the toy model mechanism in Figure 4.5. Box model measured values shown as individual data points compared to the predicted values given by Equation 4.12 (red line). In this run, _𝑘_ 3 = 1 _𝑠_<sup>−1</sup> , _𝑘_ 2 = 5 ∗ 10<sup>−8</sup> _𝑀_<sup>−1</sup> _𝑠_<sup>−1</sup> , [ _𝐴_ ]0 = 1 ppb, _𝛼_ 1 = 0 _._ 0276, and _𝛼_ 2 = 0 _._ 1.

## **4.5 Applications**

There are several possible applications of the Algorithm. Here, we have demonstrated the ability of the algorithm to quickly and accurately predict the final yields of each species in the mechanism. We have also demonstrated modifications to the algorithm which allow for calculation of species yields at any time, rather than when all reactions have gone to completion, and modifications to account for asynchronous reactants.

We have used the RYA throughout our mechanism reduction work. In the AMORE 1.0 algo-

89

rithm, it was used to help identify the key mechanistic pathways of the full mechanism. In the AMORE 2.0 algorithm, we rely on the RYA to measure the yields of all species in order to sort them in order of priority, and then it is used again to optimize a subset of the mechanism rate constants after the mechanism has been reduced. In the AMORE Gradient Descent algorithm, the RYA is used as the function whose output we are trying to optimize by tuning stoichiometric coefficients. In the GA-AMORE algorithm, the RYA is used to quickly identify which candidate mechanisms have potential to perform well by measuring the yields and comparing to the full mechanism. In each case, we take advantage of the fast runtime of RYA compared to a box model, as well as the highly interpretable results.

Although we have not tried this, it would be feasible to incorporate the RYA into a chemical transport model. For example, there might be a long list of volatile organic compounds, whose chemistry is complex but useful to keep track of. Given initial concentrations of those VOC’s, the RYA could predict the yield of various important products such as formaldehyde and SOA after a set amount of time. Rather than running at each time step of the CTM, the RYA would only need to be called whenever there was a significant change in the chemical regime (for example, the concentrations of key species such as OH and NO _𝑥_ ). The number of measurements required would be far lower than a traditional ODE solver, potentially allowing for more chemistry to be included in the model. While this method may not be quite as accurate as an ODE solver would be, it would be more accurate than omitting this chemistry altogether, or reducing to a very large degree, as is done now. It would be worthwhile to investigate this use case in the future.

90

# **Chapter 5: Error Metrics**

Throughout the process of developing and testing the AMORE algorithm, quantifying mechanism error has been essential. This is not a straightforward task, as reduced mechanisms are tasked with representing multiple species under multiple conditions in dynamic simulations. Furthermore, we are required to assess mechanism accuracy in multiple different settings, including box models, chemical transport models, and internal non-dynamic models. Each model has its own benefits and limitations.

Our error measurements range from within algorithm-measurements to post-algorithm output assessment and up to final product mechanism assessment. In the AMORE 2.0, AMORE PSO, and GA AMORE algorithms we use the Rapid Yield Algorithm (RYA) to compare the yields of specific species in the full and reduced mechanisms for optimization purposes. The benefit to this approach is that it is a very fast and is built into Python, where these algorithms are run. The RYA is at least 6 times faster than the corresponding F0AM box model, which allows for the execution of high dimensional optimization problems with a large number of iterations.

We have used the F0AM box model for the PSO AMORE algorithm, and as our general mechanism test bed for finished mechanisms. It was also used to manually optimize the AMORE v1 Isoprene mechanisms. Within F0AM, we have a range of runs we have used for mechanism analysis, which also include comparing our mechanism to experimental data.

Outside of the F0AM box model and our Python RYA model, we have run our AMORE v1 Isoprene mechanisms in CMAQ and GEOS-Chem, and have also run our reduced camphene mechanisms in the GECKO-A box model.

In this chapter, we will describe our basic error metrics and discuss how the results from other models have informed our measurements.

91

## 5.0.1 Basic Error Metric

Our basic error measurement consists of a simple error metric. The core principle of the error metric is that we are creating a quantitative measure of the disparity between a measured value in the reduced mechanism and that same error in the full mechanism. The goal is to minimize the disparity between the two mechanisms by creating accurate reduced mechanisms. This simple error metric must be measured for multiple species and conditions, and therefore it must be able to be added or averaged. Thus, the metric must have the same sign (cannot be negative), as otherwise bias in opposite directions could cancel out, leading to misleading results.

The concentrations of important species for atmospheric chemistry have a large range. For example, OH, one of the predominant reactive gases in the atmosphere, is usually in the range of 10<sup>−5</sup> ppb. In contrast, Ozone, another reactive gas is usually around 100 ppb. This is a seven order of magnitude disparity for two species of equal importance. Thus, an error metric must be independent of the scale of the species being measured.

There is also a potential disparity in scales between the reduced mechanism and the full mechanism. This poses a problem for common metrics such as percent error (Equation 5.1).



Here, T is the test or reduced mechanism value, and R is the reference or full mechanism value, and % _𝐸_ is the percent error. For example, a poorly performing reduced mechanism might have a yield of zero for a given product which has nonzero yield in the full mechanism. This would lead to an infinite disparity in order of magnitude. In terms of percent error, the error would be 100%. Conversely, a poorly performing reduced mechanism might yield a product that is not present in the full mechanism. Here, there is still an infinite disparity in order of magnitude between the two mechanisms, but now the percent error would be infinity. While the percent error is far larger in the latter case, the overall performance would be considered equally bad in the two cases. This is undesirable because it overstates the error when the reduced mechanism measurement is larger

92

than the full mechanism measurement, but also because the percent error is not bounded. Because the percent error is not bounded, summing values from multiple species might lead to a scenario in which high error in one species dominates the reported error. An ideal metric will treat order of magnitude error above the reference value equally to order of magnitude error below, and will be bounded.

From the following constraints, we have developed the following basic error metric for mechanism evaluation:



here, E is our error metric, and _𝜖_ is a very small value to prevent division by zero in the case that _𝑇_ = 0 and _𝑅_ = 0. This metric is related to the difference over the arithmetic mean reported by T � _𝑜_ rnqvist, Vartia and Vartia in their work discussing the relative benefits of various difference metrics [96]:



here, _𝐻_ 3 is the error metric defined as the difference over the arithmetic mean. The difference in our metric is that we do not divide the denominator by two, so it is twice the mean, and we take the absolute value of the difference and the absolute value of both items in the denominator. In Equation 5.3, the metric may be positive or negative and the maximum possible value is infinite if _𝑇_ and _𝑅_ have opposite signs. If they have the same sign, then the metric may go as high as 2 (at _𝑅_ = 0 and _𝑇_ ≠ 0). In contrast, our metric will never exceed one, | _𝑇_ − _𝑅_ | ≤| _𝑇_ | + | _𝑅_ | + _𝜖_ for all _𝑇_ and _𝑅_ . Furthermore, it will never go below zero as both the numerator and denominator are positive. Thus, our metric (Equation 5.2) has the following useful properties:

- It ranges from 0 to 1.

- Low bias has the same error as equal magnitude high bias.

93



<!-- Start of picture text -->
E<br>1<br>0.5<br>0.01 0.1 1 10 100 1000<br>T<br><!-- End of picture text -->

Figure 5.1: The Error Metric ( _𝐸_ ) used throughout this work given in Equation 5.2 as a function of the test value _𝑇_ (log scale) with a reference value _𝑅_ = 1.

These properties are useful because errors from multiple species or runs can be added together without error dominating the sum. Figure 5.1 shows the behavior of this metric _𝐸_ over the domain of _𝑇_ at _𝑅_ = 1. At values near _𝑅_ , the error is roughly linear with _𝑇_ , but as the disparity increases, the relative change in error decreases, such that the slope of the error function is very low when the discrepancy between _𝑇_ and _𝑅_ spans many orders of magnitude.

For this metric, a score of 0 is optimal. A score of 1 indicates that the difference in orders of magnitude between _𝑇_ and _𝑅_ is infinitely large, or that they have opposite signs. This error metric has the tendency to amplify differences near _𝑅_ and condense differences far from _𝑅_ . For _𝑇_ that is far from _𝑅_ , this metric has limitations. This is especially the case for optimization problems, where the very low gradient at _𝐸_ near 1 makes searching for optimum values difficult. To deal with this context, we have used the following equation, which is a modification of _𝐸_ to measure the order of magnitude different between _𝑇_ and _𝑅_ .

94



<!-- Start of picture text -->
4 E<br>3<br>2<br>1<br>T<br>0.01 1 100 10 4<br><!-- End of picture text -->

Figure 5.2: The Error Metric ( _𝐸_ 2) given in Equation 5.4 as a function of the test value _𝑇_ (log scale) with a reference value _𝑅_ = 1.



Here, _𝐸_ 2 is the modified error metric. Figure 5.2 shows the behavior of this metric ( _𝐸_ 2) across the domain of _𝑇_ with _𝑅_ = 1. This metric is roughly linear in the logarithmic scale of _𝑇_ , which is useful in optimization problems where _𝑇_ is much larger or smaller than _𝑅_ , as it increases roughly linearly with order of magnitude. However, this metric is not bounded and therefore has issues when either _𝑇_ or _𝑅_ is zero.

In general, we use Equation 5.2 to measure most errors.

95

## 5.0.2 Mechanism Assessment with Internal Measurements

Mechanisms have multidimensional outputs, which vary depending on the model they are run on and the conditions of the model. For example, in a box model run, the mechanism output will be a time-series of concentrations of each species in the mechanism for the duration of the run. In addition, some models track the rate of each reaction at each time step. Comparing two mechanisms is a difficult task, as there are many potential outputs to compare. There is no one measurement that will determine the accuracy of a given mechanism, so we usually compare multiple measurements. In this section, we discuss the various internal measurements we have used to compare mechanisms.

Here, internal measurements are defined as measurements that are run on a local laptop setup and rely primarily on comparison of the reduced mechanism to the full mechanism it was derived from. These measurements are computationally inexpensive and are adaptable to multiple different mechanisms with minimal adjustment. For this work, these internal measurements were made with the F0AM box model and the Rapid Yield Algorithm. In these models we have full control over the inputs and can modify the model to track various outputs, leading to a high degree of flexibility in creating mechanism measurements. Internal measurements are distinguished from external measurements, which rely on models that require significant computational resources, or utilize experimental or observed data which is mechanism specific. We will discuss these external measurements in the following section. Internal measurements are often not sufficient to fully assess mechanism accuracy. Researchers generally require that candidate reduced mechanisms be vetted in chemical transport models, or compared to experimental data. However, internal models are essential both for algorithm development, mechanism optimization, and for rapid assessment of candidate mechanisms. By utilizing both external and internal measurements, we have worked to make our internal measurements as useful as possible for determining the accuracy of a candidate reduced mechanism, in order to minimize the amount of optimization needed involving external measurements with more overhead.

A reduced mechanism will inherently have fewer species and reactions than the full mechanism

96

it was derived from. This means that not every output from the full mechanism can be considered when measuring the reduced mechanism. The standard approach is to define a set of species in the full mechanism that must remain in the reduced mechanism. This set of priority species is a reasonable choice of outputs to measure the mechanism with, as they will inherently remain in any candidate mechanism. This priority set is user-defined and system-specific.

However, there are common species that are central to all atmospheric chemistry and should usually be included in the priority set to be measured. These include O3, NO, NO2, NO3, OH, HO2, CO, the methyl radical (CH3OO), and the acyl-peroxy radical (often abbreviated as either ACO3 or CH3CO3). These species often act as reactants and products in many reactions and are the engine for continued atmopsheric reactivity. O3, and NO _𝑥_ (all of the N species) are specifically tracked for their contribution to poor air quality at high concentrations. There are many other small organic species that are prominent in most mechanisms such as formaldehyde (HCHO), which are generally included in priority species lists as well. There are many other small inorganic species which are atmospherically important, but generally do not interact with organic species directly. Another important class of species is those which contribute directly or indirectly to secondary organic aerosol (SOA). These species are system specific and are often separated into subcategories. For example, in the isoprene system, we separated SOA species as either isoprene epoxy-diols (IEPOX), isoprene nitrates, or isoprene tetra-functional compounds based off of the delineation made by Bates and Jacob et al. [30]. For camphene, we used a clustering algorithm to create 3 to 15 categories of SOA-producing species based on their volatility and Henry’s Law constants. This was done because there were over 30,000 SOA producing species, which is far too large to categorize manually.

With a set of priority species selected, there are several different quantities that can be measured and several different ways to measure them. The primary quantities of interest are the concentration, rate of production, rate of consumption, net rate of production (production - consumption), and yield. These quantities are measured for the full and reduced mechanism. The different methods of quantitative comparison include taking the difference at a specific timestamp, taking the

97

difference of the average value, or integrating the difference across each timestamp. The selection for which quantity and method to use depends on the mechanism use-case and the performance requirements.

Concentration is easy to measure and interpretable measurement to make. Comparing the concentration of a species between the full and reduced mechanism can be done qualitatively. The visual comparison shows whether the reduced mechanism generally matches the time-dependent behavior of the full mechanism. In the ideal case, the concentration of the measured species does not deviate for the entirety of the runtime. To measure the extent to which the test (reduced) mechanism matches the reference (full) mechanism for this species over the entirety of the runtime, we can take the integral of the difference in concentrations over the full runtime.



here, _𝐸𝑠_<sup>_𝑑_istheerrorintermsoftheintegraldifferenceoverruntime</sup><sup>_𝑡𝑓_,where[</sup><sup>_𝑠_]</sup><sup>_𝑇_(</sup><sup>_𝑡_)isthe</sup> concentration of species _𝑠_ for test mechanism _𝑇_ , and [ _𝑠_ ]<sup>_𝑅_</sup> ( _𝑡_ ) is the same for reference mechanism _𝑅_ . This equation mirrors Equation 5.2. Due to the requirement that the concentration must match at all time-stamps to have zero error, this metric is the most stringent error for the species being measured. However, this does not mean it is the most broadly useful. While this metric is highly stringent, its behavior at larger errors is not always useful. For example, two test mechanisms might have similar error for a given species, while one produces a final concentration much closer to the reference mechanism. This phenomenon is demonstrated in Figure 5.3. In this figure, mechanism _𝑇_ 1 shows better performance because the final concentration is closer to the reference mechanism, but the measured _𝐸𝑠_<sup>_𝑑_would not distinguish this difference.</sup>

In contrast, measuring the final concentration of the two test mechanisms would distinguish which mechanism performed better (Equation 5.6).



98



<!-- Start of picture text -->
R R R<br>T1 T1 T1<br>T2 T2 T2<br>Time Time Time<br>[s] [s] [s]<br><!-- End of picture text -->

Figure 5.3: Visual comparison of metric _𝐸𝑠_<sup>_𝑑_forspecies</sup><sup>_𝑠_fortwodifferentdifferenttestmecha-</sup> nisms _𝑇_ 1 (blue shaded area) and _𝑇_ 2 (red shaded area) compared to reference mechanism R.

here, _𝐸𝑠_<sup>_𝑡𝑓_is the single time error of species</sup><sup>_𝑠_at time</sup><sup>_𝑡_</sup> _𝑓_<sup>.For species which are not consumed in</sup> the mechanism, the concentration over time will accumulate, and the end-time concentration error becomes a suitable measure of mechanism accuracy. This measure does not account for the time it takes to reach that final concentration, but does account for the propensity for net amount of the given species produced, which may be a more important measure depending on the use-case.

While matching throughout the runtime is ideal, there is often a trade-off between short term and long term concentration matching. In this case, it is best to choose between _𝐸𝑠_<sup>_𝑑_and</sup><sup>_𝐸_</sup> _𝑠_<sup>_𝑡𝑓_mea-</sup> surements depending on which should be prioritized, or measuring either quantity at the runtime that is most preferred.

The concentration of a species evolves based on the rates of the various reactions that involve that species. The species is consumed by any reaction where it is a reactant, and produced by any reaction where it is a product.





here _𝑐_ ( _𝑡_ ) is the rate of consumption and _𝑝_ ( _𝑡_ ) is the rate of production of species _𝑠_ , where _𝑅𝑟𝑒𝑎𝑐_<sup>_𝑠_</sup> is the set of reactions where _𝑠_ is a reactant, _𝑅_<sup>_𝑠𝑠_is a product, and</sup> _𝑝𝑟𝑜𝑑_<sup>is the set of reactions where</sup> _𝑟𝑎𝑡𝑒𝑟_ ( _𝑡_ ) is the rate of reaction _𝑟_ .

99

The concentration of the species is calculated by taking the initial concentrating and taking the net rate of production (production - consumption) over the time step. Thus, accurate values for the concentration and production of the species will lead directly to accurate values of the concentration. Furthermore, any inaccuracy in the concentration may be further diagnosed by whether it was caused by bias in the rate of production, bias in the rate of consumption, or both.

Just as with concentration, the difference integral of production and consumption for a given species is a stringent measure of how well a test mechanism matches a reference mechanism.









here, _𝐸𝑐_<sup>_𝑑_</sup> _𝑠_<sup>is the difference error for the consumption</sup><sup>_𝑐_(</sup><sup>_𝑡_)of species</sup><sup>_𝑠_,</sup><sup>_𝐸_</sup> _𝑝_<sup>_𝑑_</sup> _𝑠_<sup>is the same for the</sup> production _𝑝_ ( _𝑡_ ) of species _𝑠_ , _𝐸𝑎𝑙𝑙_<sup>_𝑑_is the sum of the former two metrics, and</sup><sup>_𝐸_</sup> _𝑛𝑒𝑡_<sup>_𝑑_is the difference</sup> error for the net production _𝑝_ ( _𝑡_ )− _𝑐_ ( _𝑡_ ) for species _𝑠_ . _𝑇_ and _𝑅_ are the test and reference mechanisms respectively.

For these metrics, low _𝐸𝑛𝑒𝑡_<sup>_𝑑_signifies the net rate of production is similar between both mecha-</sup> nisms, and will also signify that the concentration will be similar as well. This is because concentration is a function of _𝑝_ ( _𝑡_ ) and _𝑐_ ( _𝑡_ ), thus _𝐸𝑛𝑒𝑡_<sup>_𝑑_=0 or</sup><sup>_𝐸_</sup> _𝑎𝑙𝑙_<sup>_𝑑_signifies</sup><sup>_𝐸_</sup> _𝑠_<sup>_𝑑_=0.In contrast,</sup><sup>_𝐸_</sup> _𝑎𝑙𝑙_<sup>_𝑑_not</sup> only measures similarity in concentration, but also measures the extent to which the consumption and production are the same as well. For example, a test mechanism might have a lower overall rate of consumption and production, with _𝑝_<sup>_𝑇_</sup> ( _𝑡_ ) _< 𝑝_<sup>_𝑅_</sup> ( _𝑡_ ) and _𝑐_<sup>_𝑇_</sup> ( _𝑡_ ) _< 𝑐_<sup>_𝑅_</sup> ( _𝑡_ ), but the following may

100



<u>J—</u> ~~'~~ <u>te )</u> (J



here _𝐸𝑐_<sup>_𝑎_is the area error using the consumption</sup><sup>_𝑐_(</sup><sup>_𝑡_) of species</sup><sup>_𝑠_,</sup><sup>_𝐸_</sup> _𝑝_<sup>_𝑎_is the same for production</sup> _𝑝_ ( _𝑡_ ), and _𝐸𝑛𝑒𝑡_<sup>_𝑎_is the net area error.</sup><sup>_𝑇_and</sup><sup>_𝑅_are the test and reference mechanisms respectively.</sup>

The integral of _𝑝_ ( _𝑡_ ) over the runtime is the total amount of species _𝑠_ produced over the run, which is the same as the yield. The integral of _𝑐_ ( _𝑡_ ) over the runtime measures the total amount of species _𝑠_ that was consumed. The difference represents the net amount of species _𝑠_ produced, and can be both positive or negative. The yield does not take into account the matching of production and consumption across time, which is beneficial in contexts where the final amount produced is more important than matching the time-dependent profile of the production curve. In general, _𝐸_<sup>_𝑎_as time-dependent matching is not usually the top</sup> _𝑛𝑒𝑡_<sup>is our preferred metric for most contexts,</sup> priority, and this method prevents against the bias shown in Figure 5.4. We prefer production and consumption based metrics over concentration based metrics. While the ultimate goal of reduced mechanisms is to replicate full mechanism concentrations, the concentration is a misleading measure as drastically different production and consumption rates can produce the same concentration profile.

Regarding production and consumption, it is important to note that there are species for which either consumption or production are negligible. This is because there is no loss (ie. no consumption) or because the consumption reactions are identical between the two mechanisms, and thus are not worth comparing. Take formaldehyde as an example. It is a common product among atmospheric oxidation mechanisms, but it does not react with organic species directly, and the formaldehyde decomposition reactions involve the same reactants regardless of the source of the formaldehyde. Whether or not formaldehyde decomposition reactions are included in the model is somewhat arbitrary, as either way, formaldehyde will be represented the same way in the full and reduced mechanism, because formaldehyde chemistry falls outside the bounds of the reduc-

102

tion. Thus, consumption does not need to be taken into account for this species, as any differences in the consumption rate will be as a result of differences in the production rate. This holds for most organic species, where consumption pathways usually are not significantly modified. In the AMORE algorithm, if an organic species remains the reduced mechanism, it will have the same outgoing reactions as in the full mechanism. The difference will be in its production pathways. Thus, production is tracked while consumption is not.

In contrast, small reactive species such as O3, NO, NO2, NO3, OH, HO2, CO, the methyl radical, and the acyl-peroxy radical are often consumed within the mechanism being reduced, and the amount of consumption will be contingent upon which parts of the full mechanism have been included in the reduced mechanism. Thus, consumption must be tracked for these species, especially the ones which are common reactants. In the isoprene mechanism, OH, O3, NO, NO3, and the organic radicals are frequent reactants, and NO2 also appears once as a reactant. Some of these species also appear prominently as products in various reactions. For example, in the isoprene mechanism, OH, HO2, NO2, CO, and the organic radicals are common products. For these species, production must be tracked as well.

Once the metric of choice has been selected, a set of box model runs must be selected to evaluate the mechanism as a whole. There are many ways to design box model runs and different runs will highlight different behaviors of the mechanism. One common method is to create a model to emulate an experiment to compare to empirical data. Another method is to utilize timeseries meteorological data to recreate a realistic representation of atmospheric conditions. We will discuss these methods in the next section, as these methods rely on data which constrains the model in a way that makes it hard to standardize the error metric.

Here, we will discuss standardized box model runs designed for measuring the error metrics described above. The goal of these box model runs is to measure the performance of the reduced mechanism. To that end, it is useful to identify specific instances where the mechanism deviates from the full mechanism. To do this, it is necessary to run the mechanisms under multiple different conditions which emphasize different mechanistic pathways. By doing multiple runs, we can take

103

multiple snapshots of the mechanism and develop a sense of which species perform better or worse, and under which conditions the mechanism performs better. This not only informs the overall mechanism accuracy, but helps to identify species and conditions that need to be improved upon.

The selection of run conditions and number of runs is an important step in mechanism measurement. There is a balance between the higher efficiency of fewer conditions and the greater information provided by more runs. Furthermore, there is also a balance between selecting conditions that emphasize specific chemical pathways, regardless of how realistic they are, and selecting conditions that are most likely to be encountered in the atmosphere at the risk of reducing the diversity of conditions. Which direction to take depends heavily on the use case of the mechanism, but here we will detail our general approach which we have applied to the isoprene mechanism.

Isoprene initially reacts with three species: OH, O3, and NO3. 80-90% is via OH, 4.5-15% is via O3, and 0.2-7% is via NO3 [30]. We include at least one condition from each of these pathways, with more contribution from the OH pathway. Within the OH pathway, 14-53.5% of the subsequent generation reacts with HO2, 6.4-73% reacts with NO, and the remainder reacts with organic radicals or a hydride-shift reaction. Thus, we include at least two high OH conditions, one which favors HO2 and one which favors NO, with a baseline concentration for organic radicals. High NO conditions are often in tandem with low photolysis rates, so the high NO condition is paired with low light conditions.

The number of conditions is proportional to the time it takes to evaluate the mechanism. While more conditions allow for a more complete assessment of the mechanism, there are diminishing returns on adding more conditions. For example, there are only so many mechanistic pathways, and not all of them are orthogonal to each other. Many conditions will produce similar product yields, and more importantly, the reduced mechanism will have similar performance over those conditions. Furthermore, adding conditions makes the results harder to interpret, as it necessitates looking through a larger set of data. For optimization processes, too many conditions makes the run prohibitively slow. For most purposes, we use a set of six conditions to measure the accuracy of mechanisms. Table 5.0.2 shows the six conditions we have used for the majority of our isoprene

104

|Run Description|ISOP|OH|HO2|NO|O3|NO3|RO2|Photolysis|
|---|---|---|---|---|---|---|---|---|
|High OH|5|0.0002|0.007|0.01|0|0|0.001|1|
|High OH and NO|5|0.0002|0.007|0.2|0|0|0.001|0|
|High O3|2|0.00001|0.007|0.01|100|0|0.001|1|
|High NO3|1|0.00001|0.007|0.1|0|0.0002|0.001|1|
|High NO3no_ℎ𝜈_|1|0.00001|0.007|0.1|0|0.0002|0.001|0|
|High Isop|10|0.0002|0.007|0.02|0|0|0.001|1|



Table 5.1: Six different run conditions used to evaluate mechanisms. All species values have units of ppb. Photolysis is a unitless constant.

## testing.

Note that the concentration of species (O3, NO, NO3, OH, HO2, and RO2) in this table are listed as constant values. Reactive atmospheric gases have concentrations that vary significantly over time (aside from very high concentration species such as O2). A model that was trying to emulate the atmosphere would let these species vary with time. However, the dynamics of these species are governed by rapid coupled reactions outside the scope of the reduction. If these reactions are included, they obscure the net production and consumption rates of these species, making it difficult to assess the error of these species and diagnose issues with the reduction. For example, when these species are allowed to vary, deviation in O3 is frequently observed in reduced mechanisms. However, this is caused primarily by NO2 chemistry which leads to the production of O3. What appears to be O3 bias is usually NO2 bias. By removing holding these small reactive gases constant, it is easier to see what the true sources of bias are. While the concentration of these species remain constant, the F0AM box model still allows the user to track the rate of production and consumption of those species by measuring the rate of reactions that consume and produce them. For example, the reaction _𝐼𝑆𝑂𝑃_ + _𝑂𝐻_ will proceed at a rate proportional to the concentration of isoprene and the fixed concentration of OH, and so we can measure the rate of consumption of OH even as its concentration remains the same. The values for isoprene in Table 5.0.2 are the initial value which is allowed to decay.

In addition to the conditions listed in Table 5.0.2, we have also developed a much larger dataset to measure mechanisms against. We utilize 1000 data points from a July 2016 single day global

105

||Isop|OH|HO2|NO|NO2|O3|NO3|Sun|Temp (K)|Air Den|( <sup>_𝑘𝑔_</sup><br>_𝑚_<sup>3)</sup>|
|---|---|---|---|---|---|---|---|---|---|---|---|
|Min.|0.10|2.5*10<sup>−7</sup>|8.0*10<sup>−5</sup>|0|0.001|4.9|1.9*10<sup>−8</sup>|0|227|0.34||
|Max.|111|9.3*10<sup>−4</sup>|3.6*10<sup>−2</sup>|5.7|18|85|1.7*10<sup>−3</sup>|0.39|315|1.3||
|Mean|2.6|8.5*10<sup>−5</sup>|7.3*10<sup>−3</sup>|0.06|0.21|28|3.3*10<sup>−5</sup>|0.011|286|1.0||



Table 5.2: The range of conditions for key atmospheric species and parameters for the GEOSChem data set. All atmospheric species are in units of parts per billion (ppb) and Sun is a unitless measure of the solar intensity relative to the maximum intensity of 1.

GEOS-Chem run. This dataset was created by selecting data points from this run where isoprene concentrations were higher than 0.1 ppb. A summary of key species and meteorological parameters is given in Table 9.1. This dataset provides a much larger range of conditions in which to compare mechanisms and serves as a useful proxy for the conditions expected in a CTM as it is derived from a CTM run.

## 5.0.3 Mechanism Assessment with External Measurements

External measurements are defined as mechanism measurements that are conducted using a model that cannot be run on a local laptop setup, or using data that was derived experimentally and is specific to one mechanism. The non-uniform nature of these measurements means that a consistent error metric cannot be created, but these sorts of measurements are necessary for validation of the mechanism, both in terms of its performance in more complex models and in its ability to match measured data.

Throughout our work we have used these sorts of mechanism measurements to validate our internal measurements and also to refine those measurements. Of all of our reduced mechanisms, the AMORE v1 Isoprene mechanism has undergone the most extensive external testing, with multiple rounds of results leading to new versions, starting v1.0, followed by v1.1, and the current version v1.2. For the AMORE Isoprene v1.0 paper [53], we conducted a box model run comparing IEPOX concentrations of the full mechanism and reduced mechanism to chamber data [61]. Figure 2.8 shows the predict and measured concentration of IEPOX, with strong agreement between the data and both the full and reduced AMORE Isoprene mechanism. This is simple case where experimental data can be used to bolster the results given by the box model, as both mechanisms

106

match one another while also matching the measured data.

In addition, our collaborators ran the mechanism in the Community Multiscale Air Quality model (CMAQ), and provided binned mean bias values from the EPA’s Air Quality System (AQS) QS measurements for formaldehyde and ozone. The measured data was compared to both our mechanism and the default mechanism based off of RACM2 [31]. Unlike prior comparisons, here we had no full mechanism to compare to, so we relied solely on the change in bias between the two mechanisms. The issue with this measurement is that we have no way to say whether the bias in the model is a result of incorrect isoprene chemistry. It may be that isoprene chemistry is incorrect even as the bias goes down, and there is no way to isolate isoprene accuracy from overall model accuracy, because isoprene-specific species are not measured. In general, the AMORE v1.0 Isoprene mechanism showed an increase in both formaldehyde and ozone, which visually appeared to correlate to lower bias, although we later discovered that ozone bias was generally worsened by the AMORE v1.0 isoprene mechanism.

In a follow-up paper, we implemented the AMORE v1.0 Isoprene mechanism in GEOS-Chem, a global 3-D model of atmospheric chemistry with data input coming from the Goddard Earth Observing System (GEOS). The baseline isoprene mechanism for this model is the Caltech Reduced Plus [30] (108 species and 345 reactions), which is far larger than the AMORE v1 Isoprene mechanism. Both mechanisms were derived from the Caltech full isoprene mechanism [16], and the baseline mechanism was considerably larger and presumably more accurate. Therefore, our goal was to minimize the differences compared to the baseline mechanism while reducing model runtime. In addition, we were able to compare this simulation to observational data to further verify the performance of the mechanism.

Our initial results showed significant ozone bias compared to the baseline and observational data. Ozone is not produced by isoprene directly in significant quantities. However, one of the primary sources of atmospheric ozone is NO2, which isoprene does contribute to. From this, we discovered significant NO2 bias in the AMORE v1.0 Isoprene mechanism due to one stoichiometric coefficient being too high. By reducing that coefficient, we were able to reduce the ozone bias

107

back to expected levels. This update became the AMORE v1.1 Isoprene mechanism.

Our initial box model testing did not catch this bias for several reasons. Principally, we had not run as many diagnostics prior to this model run, and did not realize the importance of NO2 directly to ozone. Through this process, the box model testing framework was improved to emphasize the importance of NO2, not only in itself, but as a source of ozone. Furthermore, we improved our measurement of atmospheric species such as OH, HO2, NO, NO2, O3, etc. to keep track of their production and consumption, and we developed the method which holds the concentrations of those species constant in order to more readily diagnose the source of error. Prior to the GEOSChem run, we did not know that ozone would be one of the most impacted species from isoprene chemistry, and plays an outsize role in how users view the accuracy of isoprene chemistry, more-so than many organic species.

After updating the mechanism, the AMORE v1.1 Isoprene mechanism showed less than 3% change in bias compared to observational data for ozone, NO2, PM 2.5, and formaldehyde. The AMORE v1.1 Isoprene mechanism reduced bias in ozone and formaldehyde, although this cannot be attributed to our methodology, as it is impossible to determine the extent and direction of the bias that is attributable to isoprene chemistry. The AMORe v1.1 Isoprene mechanism demonstrated a 24.6% reduction in chemical solver runtimes at low resolution and a 20.3% reduction at high resolution, leading to an overall reduction in the model runtime of 10.2% at low resolution and 2.1% at high resolution. This demonstrates the potential impact of reduced chemical mechanisms and also provides another dimension of mechanism performance.

The AMORE v1.0 Isoprene mechanism was provided as a second option for isoprene chemistry in the release of the EPA’s CRACMM mechanism [7], an updated version of their chemistry used for air quality predictions and policy impact modeling. In preparation for the release of the second version of CRACMM, we conducted testing in CMAQ to improve the AMORE 1.0 Isoprene mechanism, resulting in the AMORE v1.2 Isoprene mechanism. After the AMORE v1.1 update, observed ozone bias was much lower, however, we did also find that formaldehyde production was much higher than anticipated. After investigation, a possible cause was identified. In a

108



<!-- Start of picture text -->
4:2<br>—S— Reference As<br>_~ 1} |—*-AMORE Update An<br>2 —*-AMORE Original) —,/” mh<br>o 9.8 rs<br>& A<br>Red ite Cee ae<br>2 04 ule! geraB-O-O-o_“S$<br>Soothers, at<br>0.27 PCeeogeer™<br>0<br>05 10 15 20<br>Model Time (hrs)<br><!-- End of picture text -->



<!-- Start of picture text -->
0.6<br>petalANCONA ee<br>0.5 a<br>_~2° 0.4 if a<br>= :<br>9 °8 ; A<br>Doz fyik<br>' ¥ —S—Reference<br>0.1 —#*—AMORE Update<br>—4— AMORE Original<br>0<br>0 20 40 60<br>Model Time (hrs)<br><!-- End of picture text -->

tration of formaldehyde from the AMORE v1 Isoprene mechanism, which had to be reduced by lowering the overall yield of formaldehyde.

For the AMORE v1.2 Isoprene mechanism, we opted to lower the formaldehyde yield to match the diurnal cycle run, which was more representative of the CMAQ 3-D transport model where the mechanism would be used. A follow-up study focusing on formaldehyde in the CRACMM2 mechanism showed that the incorporation of the AMORE v1.2 Isoprene mechanism lead to an average increase in formaldehyde of roughly 0.5 ppb in the Southeastern United States [56]. This update reduced the bias in the model considerably, as the formaldehyde concentrations were considerably lower than the measured concentrations in the previous default isoprene mechanism [31]. Furthermore, the bias decreased in regions where isoprene chemistry is most prevalent, which signifies a potential reduction in overall isoprene mechanism bias. This reduction in isoprene bias allows researchers to identify and focus on other areas where the model shows bias, leading to future avenues for model improvement.

The results from Chemical Transport Models are inherently more qualitative in nature, as it is not possible to quantify the accuracy of the isoprene mechanism as a standalone entity. However, these studies demonstrate ways to measure the accuracy and performance of reduced mechanisms, and show how improved reduced mechanisms can aid in our understanding of atmospheric processes.

110

# **Chapter 6: Particle Swarm Optimization for Reduced Mechanisms**

## **6.1 Introduction**

In this chapter, we present the use of particle swarm optimization (PSO) to optimize stoichiometric coefficients and rate constants for the recently published AMORE-Isoprene mechanisms v1.1 and v1.2 [53, 97, 56], referred to as AMORE v1.1 and AMORE v1.2 respectively throughout the rest of the text. With this method, we are able to improve mechanism performance by optimizing the mechanism with respect to a select set of priority species (see Section 6.3.2) in order to more closely match the full mechanism that these reduced mechanisms were derived from. We define an objective function to minimize using an error metric (see Section 6.3.2) to quantify the ability of the reduced mechanism to match the output of the full mechanism. PSO was chosen because it is an efficient method that can optimize a large number of parameters with an objective function that is computationally costly to evaluate. We undertook this project to address the need for automated optimization of reduced chemical mechanisms. As automated mechanism reduction becomes more widely available, there will be a greater need for reduced model optimization to improve the resulting mechanisms. We demonstrate PSO for these reduced gas-phase isoprene mechanisms as an example of the utility of this method, with the potential for it to be applied to other systems.

The AMORE v1.1 and AMORE v1.2 mechanisms are reduced isoprene mechanisms developed from the Caltech isoprene mechanism [16] using a mechanism reduction algorithm. The AMOREIsoprene mechanisms were created using a graph-theory-based algorithm that measures the sensitivity of the full mechanism to a wide range of input conditions and creates a set of reduced mechanistic pathways that have output similar to the full mechanism. This algorithm was motivated by the need to create highly reduced volatile organic compound (VOC) oxidation mechanisms for use

111

in computationally expensive 3D chemical transport models, which are used to model atmospheric aerosol formation, and air quality. In complete chemical models, rate constants and stoichiometric parameters are constrained by experimental results and conservation laws. However, in reduced models, such as the AMORE v1 isoprene mechanisms, the mechanism is condensed to a small set of species with much fewer reaction generations. Thus, the yields of products actually represent a much more complex chemistry, and so stoichiometric coefficients are not well-constrained in all cases. Rate constants are averaged over several reactions, and sometimes represent multiple generations of chemistry, and therefore are not well constrained either. Furthermore, the current state of the art requires manual tuning of stoichiometric coefficients and rate constants, so there is much potential for improvement. The AMORE v1 mechanism was initially developed and tested in CMAQ [53]. Subsequent GEOSChem modeling lead improvements and the release of AMORE v1.1 [97]. The mechanism was updated once more, by removing some less significant reactions, adding in new secondary organic aerosol producing species, and recalibrating stoichiometric coefficients. This update was tested in CMAQ and released as AMORE v1.2 [56]. Both AMORE mechanisms have undergone rigorous testing for use as reduced isoprene models in chemical transport models. While both mechanisms originate from the same original mechanism, they have sufficiently different reactions and products to warrant separate treatment for optimization. These mechanisms along with our optimized mechanisms are available in the supporting files.

Optimization of stoichiometric coefficients and rate constants for chemical reaction mechanisms is not trivial, and represents a substantial bottleneck in the generation of accurate reduced mechanisms. The candidate reduced model is tasked with accurately representing the full chemistry in terms of the consumption and production of several priority species over a wide range of atmospheric conditions. For our work, we have developed a box model testing protocol to compare a candidate reduced mechanism to the full mechanism. This protocol involves running the full mechanism and candidate reduced mechanism under multiple conditions (Table 8.2.1) and comparing the net production and consumption of multiple priority species. We have developed a quantitative error metric (see Section 6.3.2) which our optimization seeks to minimize. Multiple

112

box model runs are required to measure the error metric of a candidate mechanism, there is a high computational cost to measure the objective function that is being optimized. Additionally, mechanism parameters are highly coupled, and changes in one parameter often impact the optimal value for many other parameters. This means that parameters must be optimized simultaneously and that there are many potential local minima in the objective function. Although reduced mechanisms are considerably smaller than the full mechanisms on which they are based, they still contain a large number of parameters. For example, the AMORE v1.2 mechanism contains 107 stoichiometric coefficients, and 22 rate constants. The high number of coupled parameters (stoichiometric coefficients and rate constants) to optimize, combined with the relatively slow objective function evaluation time, makes this a challenging optimization problem.

The remainder of this paper is organized as follows: in Section 6.2, we discuss the problem of chemical reaction modeling, and present a brief overview of the methods used to optimize reduced chemical mechanisms. In Section 7.2, we outline the details of the particle swarm optimization algorithm, and how it has been adapted to our problem of optimizing stoichiometric parameters for reduced chemical reaction mechanisms. This is followed by presenting the results in Section 7.3 for the reaction mechanisms under study, atmospheric gas-phase isoprene oxidation, for both variants, namely AMORE v1.1 and AMORE v1.2. Finally, in Section 6.5 we conclude and summarize our work presented in this article.

## **6.2 Background**

## 6.2.1 Particle Swarm Optimization

The evolutionary optimization strategy employed in this article is particle swarm optimization (PSO) [98]. It belongs to a class of _nature-inspired_ computing techniques [99] for optimization, termed swarm intelligence [100]. PSO has been deployed in a wide range of applications because of the versatility of the approach for challenging optimization processes. These applications include chemical mechanism analysis [101, 102], parameter estimation [103], dynamic optimization [104, 105, 106], forecasting [107], data clustering [108], training feedforward neural networks

113

[109], robotics [110], smart grid design [111], astronomy [112], manufacturing [113], and additional applications [114]. Within the field of atmospheric chemistry, PSO algorithms have been used for various problems, including parameter optimization for custom instruments [115], identifying atmospheric gas species sources [116, 117, 118], predicting concentrations of select species and particulate matter [119, 120], and estimating particle size distributions [121].

A major benefit of using PSO is that we can choose to impose first-principles-based constraints on the optimization, which include bounds and heuristics for the optimization variables. This is an avenue for the inclusion of domain knowledge in the modeling framework, resulting in a hybrid artificial intelligence (AI) approach [122]. PSO belongs to the class of evolutionary algorithms, which is inspired by the process of evolution as observed in nature. These have had success in domains such as model discovery [123, 124], structure-to-property prediction [125], process systems engineering [126, 127], inverse design [128], materials design [129], and many others [130].

Inspired by the movement of a flock of birds, PSO attempts to model the collective intelligence of particles (or agents) toward the optimization of a global objective while adhering to local rules. It relies on a combination of global and local search by weighting their respective deviations, such that it is able to sufficiently explore the search space of objective variables while honing in on well-performing spaces that result in the optimization of the objective function. Its strength, which enables its applicability to a myriad of domains, is due to having a limited set of tunable parameters, and relatively simple update rules as one proceeds from one iteration to the next. As an evolutionary algorithm, we must point out that one of the drawbacks is that the algorithm does not ensure that the optimal value obtained after the pre-specified iterations is the global optimum. Accordingly, we must proceed with additional runs and save the best-performing optimal value(s).

## **6.3 Methods**

We employ, particle swarm optimization, a derivative-free optimization to optimize the stoichiometric coefficients and rate constants of the reduced chemical mechanisms (AMORE v1.1 and AMORE v1.2). A derivative-free optimization is defined as one which does not utilize the

114

derivative of the objective function in order to determine the next step in the optimization. This is in contrast to gradient based approaches, which utilize the derivative of the objective function to determine the next step. The reason for a derivative-free evolutionary optimization approach is three-fold. First, by virtue of the problem formulation, there is no unique mathematical function that can accurately and reliably map the multiple coefficients (stoichiometric and/or rate constants) to a continuous function, for every discrete possibility of reactant(s) and product(s). Accordingly, it is not possible to evaluate a gradient of the same. Second, the use of an evolutionary optimization scheme allows exploration of the huge parameter space, which is often a shortcoming of gradientbased approaches. With gradient based approaches, the number of error measurements needed is proportional to the number of optimizable parameters. As mentioned in Section 6.1, there are more than 100 parameters for the reduced chemical mechanisms used in this work, making gradient based approaches infeasible. On the other hand, evolutionary optimization methods do not require more error measurements for more optimizable parameters, and thus are not as computationally constrained by larger systems. Third, a derivative-free approach is able to escape local minima unlike gradient-based approaches.

PSO is well-suited to the problem discussed in this article for several reasons. First, the search space is high-dimensional (equal to the number of free-roaming stoichiometric coefficients and rate constants), meaning that the search space is very large. Second, there are multiple local minima in the objective function, which can be more readily explored using stochastic methods. Finally, the computational cost to measure the objective function on an individual mechanism is high. Taken together, these features favor an approach, such as PSO, which efficiently explores the search space in a stochastic manner, is derivative-free, and requires a low number of objective function evaluations. We note that PSO is an exemplar of an evolutionary optimization algorithm that is simple and particularly well-suited to our scenario, but it is not the only evolutionary algorithm that could potentially be applied. PSO is designed for continuous rather than discrete variables. In our case, we are optimizing stoichiometric coefficients and rate constants, which are both continuous variables, making PSO an appropriate choice. There are many evolutionary algorithms that differ

115

from PSO in terms of specific implementation, but all utilize populations of parameter sets that evolve over the course of generations. We chose PSO because it is the most well-studied within its class of algorithms. In the subsequent subsections 6.3.1 and 6.3.2, we discuss the PSO algorithm and the objective function used in this study, respectively.

## 6.3.1 Particle Swarm Optimization

Particle swarm is an optimization algorithm that seeks to minimize the value of a user-defined objective function by modifying the optimizable parameters which are inputs to that function. Consider an objective function _𝑓_ ( _𝑥_ ) : R<sup>_𝑛_</sup> → R that we wish to optimize. For our current problem, we minimize the difference between the net production of a select set of priority species predicted by our reduced mechanism, and that predicted by the full mechanism. The objective of PSO is to minimize this difference, which it does by changing the values of the stoichiometric parameters and rate constants of the reduced mechanism such that optimal parameters are obtained. These stoichiometric parameters and rate constants are the optimization variables in this problem.

At the start of the algorithm, several sets of random optimization variables are generated. These variables can be thought of as _particles_ in a space of _𝑁_ dimensions, where each instance is the location of the particle. Thus, the goal is to find the optimum position of the particles that minimizes the value of the objective function _𝑓_ ( _𝑥_ ). Let<sup>−→</sup> _𝑔_ ( _𝑡_ ) denote the best position the algorithm has encountered in iteration _𝑡_ , and<sup>−→</sup> _𝑝_ denote the best position the algorithm has encountered since the start of the algorithm. Let<sup>−→</sup> _𝑥 𝑖_ ( _𝑡_ ) denote the position of the particle _𝑖_ during iteration _𝑡_ . This position is updated when the particle _moves_ to a new position with some velocity _𝑣𝑖_ ( _𝑡_ ). These positions are updated based on update rules as follows:





116

Here, _𝜔_ 1 and _𝜔_ 2 are random numbers uniformly sampled between 0 and 1. These incorporate stochasticity into the calculation of velocity of the particle. _𝜔_ 1 and _𝜔_ 2 are constant parameters that weigh the emphasis given to deviation from the best globally and locally performing particles in the swarm respectively. _𝜒_ is termed the inertia weight, which is a measure of the contribution of the previous velocity of a particle to its current velocity[131]. Based on an agent’s new velocity, its position is updated. Together, these terms determine the balance between exploration (global search) and exploitation (local search) in PSO. This is repeated for the pre-specified number of iterations until we obtain the best-performing particles. The algorithm ensures that the best-performing particle is at least at par with the optimum in a previous iteration, but not worse, unlike gradient descent which can overshoot depending on the learning rate. This is unlike gradient-based approaches, where due to an incorrect choice of the learning rate, the search for the optimum value(s) across the loss landscape leads to overshooting and/or divergence. Due to PSO algorithm’s inherent stochastic nature, it is recommended to run the algorithm for a few runs, as the optimum obtained after the pre-specified number of iterations can vary. This also mitigates the risk of getting stuck in a local minimum of the objective function.

The progression of the PSO on a sample reduced mechanism from one iteration to the next is depicted in Figure 6.1. Since we use MATLAB[132] for the problem discussed in this article, we refer the reader to the implementation of PSO Global Optimization Toolbox[133], which includes modifications from Mezura-Montes and Coello Coello[134], and Pedersen[135].

## 6.3.2 Objective Function

In our problem, the objective function is an aggregate measure of the fidelity of the net production rates of priority species as obtained from the reduced mechanism, compared to those obtained from the full mechanism. This is measured under six different conditions shown in Table 8.2.1, pertaining to isoprene-relevant conditions that occur in the atmosphere. Thus, we choose to minimize this objective function, as a lower objective function value quantitatively corresponds to a more accurate condensed representation of the full mechanism.

117



<!-- Start of picture text -->
OH | 0.06 OH} 0.06<br>ISOPOO 1.86 ISOPOO 2186<br>02] 0.13 double<br>OH NOs 1.62 OH 1.62<br>ane —<br>(siti doubles,<br>, 1.22 OH / 1.22 OH<br>‘ P<br>/ No “ox No<br>ey<br>4 OH 0.79 0.79 , <><br>0.83 \11.44 l O;\ 1.44<br>O3 ‘, \ aeAAS uece \ aie.a.<br>\ coer<br><!-- End of picture text -->

meant to capture the variety seen in the atmosphere. In general, greater or fewer input conditions can be selected, inducing a trade-off between computational cost and atmospheric representation. This trade-off is also influenced by the variety of situations in which the mechanism being tested is relevant. In the case of the isoprene mechanism, we chose six different input conditions meant to select the most relevant conditions for isoprene. Table 8.2.1 lists these conditions. The set of conditions is provided as an input to the objective function evaluation, and all mechanisms are evaluated on all conditions. Although not addressed here, optimally selecting the input conditions is an orthogonal problem to pursue in future work.

The isoprene mechanism influences several important atmospheric species, including OH, HO2, NO, NO2, ozone (O3), formaldehyde (HCHO), and isoprene epoxy-diol (IEPOX), lumped isoprene nitrates (ISOPN), glyoxal (GLY), methylglyoxal (MGLY), methyl vinyl ketone (MVK), and methacrolein (MACR). We note that these priority species are user-defined and more or less of them can be included in the optimization process depending on model goals. The function includes individual performance metrics for each of the priority species involved in the mechanism, which are given an importance weighting based on the environmental context. In order to take into consideration the performance of the mechanism across multiple species and conditions, the objective function consists of a weighted average of individual species-run performance metrics. A species-run is defined as a simulation of an individual species under one set of input conditions. The following weights were used for our model runs: OH, 1; HO2, 1; NO, 1; NO2, 1; O3, 1; formaldehyde, 1; isoprene, 0.5; IEPOX, 1; methylglyoxal, 0.5; glyoxal, 0.5; CH3CO3, 0.8; CH3OO, 0.8; methacrolein, 0.5; methyl vinyl ketone, 0.5; isoprene nitrates, 0.8. These weights are user-defined and depend on the priorities of the reduced mechanism. All of our priority species have weights in a narrow range of 0.5 to 1, which prioritizes breadth of improvement, but we do assign heavier weighting to small inorganic species and the most important organics. Changing the weights will have no impacts on the optimization process aside from changing the final optimized result.

The ultimate performance goal of the reduced mechanism is to accurately match the concen-

119

|Run Description|ISOP|OH|HO2|NO|O3|NO3|RO2|Photolysis|
|---|---|---|---|---|---|---|---|---|
|High OH|5|0.0002|0.007|0.01|0|0|0.001|1|
|High OH and NO|5|0.0002|0.007|0.2|0|0|0.001|0|
|High O3|2|0.00001|0.007|0.01|100|0|0.001|1|
|High NO3|1|0.00001|0.007|0.1|0|0.0002|0.001|1|
|High NO3no_ℎ𝜈_|1|0.00001|0.007|0.1|0|0.0002|0.001|0|
|High Isop|10|0.0002|0.007|0.02|0|0|0.001|1|



Table 6.1: Six different run conditions used to evaluate mechanisms. All species values have units of ppb. Photolysis is a unitless constant.

tration of the priority species in the full mechanism. The rate of production and consumption are the two forces that influence the overall concentration of the priority species. Our error metric is defined using the net production and consumption of a given species. We note that other metrics can be used involving concentration, time-dependent production rates, or any other user-defined quantity. The isoprene mechanism influences primarily the production rate of several priority organic species and also the production and consumption rate of some reactive background species. In order to quantify the performance of a mechanism, the error must be calculated for each species with simulation results from each input condition. The combination of results from a single species under a set of conditions is termed a species-run. A useful species-run metric is normalized, so that averages can be taken without being skewed by significantly higher or lower values. The production and consumption rate of the priority species in the isoprene mechanism varies over time as the mechanism simulation progresses. The species-run metric captures this time dependence by integrating the difference in production and consumption rates of the target species between the test and reference mechanism over the entire run time. It must be noted that the reference mechanism was run on the same box model. The sum of the reference and test values is used as the denominator so that the quantity is normalized to be less than or equal to one. The following equations give the metric used for the individual species run, which was averaged to create the objective function:



120









Here, _𝑥_ represents a set of input conditions, _𝑠_ represents the priority species being measured, _𝑇_ denotes that the test mechanism is being measured, _𝑅_ denotes that the reference mechanism is being measured, _𝑝_<sup>_𝑇_</sup> _𝑥,𝑠_<sup>(</sup><sup>_𝑡_) represents the rate of production of species</sup><sup>_𝑠_with input conditions</sup><sup>_𝑥_using</sup> mechanism _𝑇_ , _𝑐_<sup>_𝑇_</sup> _𝑥,𝑠_<sup>(</sup><sup>_𝑡_) represents the rate of consumption of the same,</sup><sup>_𝛼𝑠_is a binary variable which</sup> denotes whether or not consumption should be taken into account for species _𝑠_ , _𝐶𝑥,𝑠_<sup>_𝑇_and</sup><sup>_𝑃𝑇_</sup> _𝑥,𝑠_<sup>repre-</sup> sent the total net consumption and production of species _𝑠_ with input conditions _𝑥_ for mechanism _𝑇_ over the total run time from _𝑡_ 0 to _𝑡 𝑓_ respectively, and _𝑓𝑥,𝑠_ ( _𝑇, 𝑅_ ) represents the species-run error metric. The error metric ranges from 0 to 1, where 0 represents perfect alignment with the entire mechanism, and 1 represents an infinite deviation from the reference mechanism. Only test mechanisms that represent and match the net production and consumption rate of each species will have a error metric of 0. Equation 8.4 shows the overall objective function used for a test mechanism.



Here, _𝐹_ ( _𝑇, 𝑅_ ) is the objective function for a mechanism T compared to the reference mechanism R, _𝑋_ represents the set of all test conditions, _𝑆_ represents all the priority species being measured, _𝜔𝑠_ represents the weighting assigned to a given species, and _𝑓𝑥,𝑠_ ( _𝑇, 𝑅_ ) is given in equation 8.3. By virtue of the problem formulation, we can explore a few orders of magnitude of the

121

acceptable rate constants, and similarly, for stoichiometric coefficients, we can search within a user-defined range. Here, the rate constants were allowed to perturb within 2 orders of magnitude of the previously user-defined default values, which served as a reasonable starting point for the algorithm. The stoichiometric coefficients of the products were restricted to be within 0 _._ 01 to 2. The reactant stoichiometric coefficients were held constant. These stoichiometric coefficients and rate constant values are the optimization variables used in PSO. We first optimize only the stoichiometric coefficients while keeping the rate constants the same, and obtain their results. Separately, we optimized the stoichiometric coefficients and rate constants simultaneously. This was done in order to investigate the effect of including rate constants on optimization results.

In the next section, we present the results of optimizing the AMORE v1.1 and AMORE v1.2 reduced mechanisms, using both: only stoichiometric parameter optimization, and stoichiometric and rate constant optimization. The results of the same are compared to the concentration plots obtained from the AMORE v1.1, AMORE v1.2, and the Caltech Isoprene mechanism designed by human experts [53, 16]. We note that the optimized reduced mechanisms are expected to be no more or less computationally efficient than the reduced mechanisms they are derived from, since they contain the same number of species and reactions. Rather, the purpose of this optimization is to improve upon an existing reduced mechanism without impacting computational cost.

## **6.4 Results and Discussion**

We conducted several runs of the PSO algorithm on the AMORE v1.2 mechanism. All PSOoptimized mechanisms scored better on the objective function than the AMORE v1.2 baseline mechanism. We ran the optimization using different particle populations and number of generations. Based on conventional evolutionary optimization terminology, _population_ refers to the entire collection of optimization variables. Thus, a population of 50 individuals would have 50 instances of N-dimensional optimization variables, with each set of N-dimensional optimization variables being referred to as an _individual_ . _Generation_ refers to the iterations of the optimization algorithm.

122



<!-- Start of picture text -->
=== population size = 5<br>0.45 *== population size = 25<br>v === population size = 50<br>G 1% === population size = 100<br>c 0.40 \<br>Oo s as —— . — = = —<br>ra s ~<br>Pa ‘ \ ~ =< =<br>=) sae Som XN<br>yp 039 . * a VT<br>> as .. *<br>‘2 0.30 TT ay \<br>oO oe8 > —<br>". e<br>“)<br>0.25<br>0 200 400 600 800 1000 1200<br>Total different parameter sets tested<br><!-- End of picture text -->

of 0.4697, and the 25 particle population run had the lowest initial objective functional value of 0.3851.

Each run starts at a different number of parameter sets tested, since the starting point represents the best fitness after the first generation of parameter sets has been tested. In all cases, the objective function decreases rapidly at first and more slowly as the optimization goes on. From the data, we can see that, initially, small particle populations are able to descend more rapidly towards a better objective function score, but more quickly reach a plateau where the descent is much more gradual. Larger particle populations tend to show a much slower initial descent that is sustained for a longer period. This can be explained by the fact that for larger particle populations, each generation requires more parameter sets to be tested, leading to a much slower convergence towards the vicinity of the best particle.

The 5 particle population run achieved a final objective function score of 0.2693 after 1255 parameter sets tested. Due to the small population, this run hit a clear plateau after 227 generations, showing no improvement in the subsequent 24 generations. The 25 particle population run achieved a final objective function score of 0.2076 after 6275 parameter sets tested. The 100 particle population achieved a final score of 0.2125 after 5700 parameter sets tested. The 50 particle population run achieved a objective function score of 0.2277 after 1850 parameter sets tested, and was on pace to outperform the 25 particle population run. The results demonstrates diminishing returns as particle population increases, as well as the inherent variability in runs. However, the dataset is not large enough to draw conclusions about the optimal generation size, and due to the stochastic nature of the algorithm, results will vary significantly between runs.

We investigated the amount of variation between identical runs using a 10×20 optimization of the AMORE v1.2 stoiciometric coefficients with the original mechanism as a seed particle and +/30% of the original value as constraints on all coefficients. We ran this optimization ten separate times. The initial best score ranged from 0.2785 to 0.2863 with a percent standard deviation of 1.0%. The final best score ranged from 0.2476 to 0.2567, with a percent standard deviation of 1.19%.

124

It took approximately 5 seconds to test a single parameter set on each of the six conditions (on the Dell 2000 MHz Inspiron 15 8-core laptop with 16 GB RAM which was used in this work). Our longest run took approximately 8 hours, but we were able to achieve significant improvement on runs that were only one hour long. We used generations of 25-100 depending on the particle population and desired runtime. For a given mechanism, we found that there was a minimum objective function score that multiple runs converged towards. For example, none of the AMORE v1.2 mechanism were able to achieve a fitness value below 0.2, while several were able to achieve a fitness value below 0.23, as demonstrated by the final values described above. While we do not know what the global minimum is for a given mechanism, we do know that it is influenced by the structure of the mechanism itself, and therefore there is a limit to the amount of improvement that is possible.

The optimal population will depend on the use case, but particle population should roughly scale with desired runtime. As shown in Figure 6.2, there are diminishing returns in running the algorithm near the plateau value, which will be reached more quickly in a small particle population. Likewise, the initial descent will tend to be slower in larger particle populations, leading to marginal improvement if the number of generations is too small. From our testing, particle populations of 50 with 100 generations are an ideal balance between runtime and model improvement. Increasing constraints and using seed particles will generally reduce the particle population size required and the number of generations needed. In general, choosing smaller population sizes leaves the search of optimal solutions to chance while larger population sizes result in much more compute while promoting only the best obtained individuals. Thus, it is more likely that locally optimal solutions get carried forward through the generations without exploring the parameter space sufficiently[136, 137].

We chose a selection of our best PSO mechanisms for a more detailed analysis. These mechanisms include two optimized variants of both, the AMORE v1.1 isoprene mechanism, and the AMORE v1.2 isoprene mechanism. For both, we first optimize only the stoichiometric coefficients, followed by optimization of stoichiometric coefficients and rate constants. All optimiza-

125

|Mechanism|AMORE<br>v1.1|AMORE<br>v1.1|AMORE<br>v1.1|AMORE<br>v1.2|AMORE<br>v1.2|AMORE<br>v1.2|
|---|---|---|---|---|---|---|
|||PSO|PSO<br>+<br>rates||PSO|PSO<br>+<br>rates|
|High OH|0.42|0.27|0.16|0.27|0.19|0.16|
|High OH+NO|0.35|0.31|0.34|0.28|0.23|0.24|
|High O3|0.29|0.12|0.18|0.30|0.21|0.16|
|High NO3|0.34|0.32|0.24|0.27|0.19|0.21|
|High NO3<br>no|0.35|0.36|0.35|0.33|0.29|0.29|
|hv|||||||
|High Isoprene|0.39|0.26|0.15|0.27|0.17|0.16|
|Average|0.36|0.27|0.24|0.29|0.21|0.20|
|% improvement|-|**24.0**|**28.7**|-|**26.2**|**28.8**|



Table 6.2: Table showing measured fitness values for six reduced isoprene mechanisms under six different testing conditions.

|Mechanism|AMv1|.2 AMv1.2|AMv1.2<br>AMv1.|1 AMv1.|1<br>AMv1.1|
|---|---|---|---|---|---|
|||PSO|GeosPSO|PSO|GeosPSO|
|Average Score|0.29|0.38|0.27<br>0.32|0.37|0.28|
|Standard Devi-<br>ation|0.05|0.11|0.07<br>0.06|0.07|0.08|



Table 6.3: Table showing mean and standard deviation of measured fitness values for six reduced isoprene mechanisms under 1000 different testing conditions derived from a global GEOS-Chem simulation.

tions were performed for 100 generations with a particle population of 50. This was the largest run that we were able to do on our system within an 8 hour runtime. Table 6.4 shows the fitness values for each optimized mechanism, and the mechanism it is optimizing. The optimization of the PSO without rate coefficients was able to improve the AMORE v1.1 mechanism by 24.0%, and improve the AMORE v1.2 mechanism by 26.2%. With the rate constants included in optimization, the AMORE v1.1 mechanism was improved by 28.7% and the AMORE v1.2 mechanism was improved by 28.8%. The PSO optimization had strong breadth of improvement in all six testing conditions. The AMORE v1.1 PSO with rates, AMORE v1.2 PSO, and AMORE v1.2 PSO with rates performed equal to or better than the original mechanism for every condition tested. The AMORE v1.1 PSO was better than the original mechanism for five out of six conditions, and had a slightly worse performance under high NO3 low light conditions.

126



<!-- Start of picture text -->
—©—Reference Mechanism<br>—*— AMORE v1.1<br>—4— AMORE v1.1 PSO Optimized<br>4 _. 0.07<br>rs p 1.2 2 0.06<br>= of 08 © 0.04} / %<br>O27 3 £ EPA<br>= -osle < 5 4<br>1 “ie >. o 002 4<br>0.29 a, S001,<br>0 0 5 10 15 20 0 0 5 10 15—— 20 4 5 40 415 20aEERG »)<br>Model Time (hrs) Model Time (hrs) Model Time (hrs)<br>1 1 0.25<br>s 08) & , 0.8 | / 02 £ zoe<br>206) f a if ry f<br>> |2 B06 fi| xDo15) «42<br>4 i a iS re A<br>@ 0-4/4 9 0.45 7 0118<br>0.2) 02 0.05 3<br>0 f 0 0<br>0 5 1018 20 0 5 10 15 20 0 5 10 15 20<br>Model Time (hrs) Model Time (hrs) Model Time (hrs)<br><!-- End of picture text -->

in Figure 6.3, the performance in improved to near zero error (looking at end concentrations) for formaldehyde, IEPOX, methylglyoxal, and glyoxal, with a marginal increase in error for isoprene nitrates, and no change for methacrolein. For the AMORE v1.2 results shown in Figure 6.4, there is a reduction in error for methyglyoxal and methacrolein, little change for IEPOX and isoprene nitrates, and an increase in error for formaldehyde and glyoxal. We note that end concentrations are not the only metric for accuracy, but the optimization error metric prioritized end concentrations by focusing on net production and consumption. Thus, end concentrations are a good indicator of the performance of the optimization. Using a different error metric is fully compatible with the PSO method and would yield different results.

We conducted further investigation into the increased error in formaldehyde, and identified the isoprene + OH reaction formaldehyde product coefficient as the key difference between the unoptimized and optimized AMORE v1.2 mechanisms (see supporting files for mechanism details). The optimized mechanism had a lower stoichiometric coefficient for formaldehyde, leading to lower concentrations than the reference mechanism. The stochastic nature of the PSO algorithm means that particles will have parameters that are not perfectly optimized. This set of parameters was selected in spite of the bias incurred from the identified coefficient, because in aggregate, it had a higher performance. In general, there is a trade-off between increasing breadth of improvement by having several species in the objective score, and extent of improvement, by having fewer heavily weighted species in the objective score.

This error can be counteracted by identifying a species for further improvement and isolating its coefficients. We ran a 10x10 PSO optimization using the original optimization as a seed particle, and only changing stoichiometric coefficients involving formaldehyde. The formaldehyde error score (8.3) decreased from 0.13 to 0.040 with the additional optimization, much lower than the formaldehyde score of 0.058 in the original mechanism. The overall mechanism objective function value decreased from 0.21 to 0.20, showing that no trade-offs arose from this isolated optimization. PSO is additive by nature, meaning that optimizations can be done sequentially to the same mechanism, allowing for this process to continue until the user has achieved the desired

128

level of accuracy.

Figures 6.5 and 6.6 compare the deviation from reference value of PSO-optimized mechanisms to the AMORE baseline mechanisms for six of the most important species under the six different testing conditions (specified in Table 8.2.1). There is variation in the deviations between species and conditions, but on average, there is a significant reduction in deviations from the AMORE mechanisms to the PSO mechanisms. We selected a few species to highlight for causal explanations. For the AMORE v1.1 based mechanisms, the stoichiometric and rates optimization did well for HO2.

We identified the reaction of ISOPOO with HO2 as the cause of this performance change. In the original mechanism, this reaction produces 0.6 moles of HO2, whereas in the optimized mechanism it produced 1.72 moles of HO2. This substantially increased HO2 production accounts for the higher net production of HO2 in the full mechanism due to production from more oxidized compounds that are removed from the reduced AMORE mechanism. The stoichiometric optimization did well on OH under high O3 conditions. The full mechanism has a net production of near zero for OH under high O3 conditions as a result of OH production from the reaction of isoprene with OH compensating for the consumption of OH reacting with isoprene. The optimized mechanism increased the yield of OH in the reaction of isoprene with O3 leading to stronger agreement. For the AMORE v1.2 based mechanisms, both optimizations performed well for HO2, particularly under high OH and NO conditions. We identified the ISOPOO + NO reaction as the key reason for improved performance. The yield of HO2 went from 0.48 in the original mechanism to 1.67 in the stoichiometric optimization and 1.83 in the optimization with rates, leading to more HO2 production in line with the full mechanism. For both sets of optimization, NO had higher bias than the original mechanism. In both versions of AMORE, NO is consumed rather than produced, and the key reaction involved in NO consumption is ISOPOO+NO. We found that the yield of ISOPOO in the optimized mechanisms was reduced, and the product yields from ISOPOO were increased to compensate for the reduced yield. However, there was no way to compensate for reduce NO consumption, leading to higher bias. This impact could be fixed by imposing a limit constraint on

129

the ISOPOO yield. We describe the results of a constrained run in the following paragraph.

The randomness associated with PSO may be undesirable in some use cases. The primary benefit of PSO’s randomness is in its ability to optimize under strict time constraints where other methods, such as gradient descent, will not work. However, there are constraints that may be added to PSO to ensure a baseline level of improvement and reduce undesired outcomes. One method to ensure a baseline of performance is to include a seed particle in the particle swarm optimization. This seed particle represents an existing set of coefficients, such as the original coefficients or a previously optimized set of coefficients. This method ensures that the optimized result will be no worse than the seed particle, and will generally be much better than the seed particle. Additionally, tighter constraints can be set for the parameters. In the case of our original runs, we used no seed particles, and set relatively generous bounds of 0 to 2 for each of the optimized stoichiometric coefficients. On the one hand, this allows the PSO to explore a much larger space, but the drawback is that the optimization is starting from scratch, and has to make up some ground before it is at the same level of performance to the original mechanism. To demonstrate the versatility of the method, we ran a 25×25 optimization on the AMORE 1v.2 mechanism with a seed of the original mechanism and constraints on each parameter such that they could vary by no more than 30% above or below their original value. Additionally we select isoprene-based species coefficients, such as ISOPOO, to preserve their yield. After 625 parameter sets tested, this run achieved an objective function score of 0.24, an improvement of 19.5% over the AMORE v1.2 baseline. Notably, the score for NO under high NO conditions was 0.004, compared to 0.28 and 0.30 for the two unconstrained AMORE v1.2 PSO mechanisms. This shows that constraints have the ability to minimize unwanted results in species specific cases.

Improvement in one set of conditions may not lead to improvement in another set of conditions. While our selection of conditions was not arbitrary, it does not necessarily reflect the full breadth of atmospheric condtions. In order to demonstrate the ability of the algorithm to work across a diverse set of conditions, we utilized species concentration and meteorological dataset derived from a 200km gridded global GEOS-Chem simulation for 24 hours on July 1 for the year 2016. From this

130

dataset, we randomly selected 1000 data points in which the concentration of isoprene was above 0.1 ppb. In this dataset, conditions range from 0.1 ppb to 110.7 ppb for isoprene, 2 _._ 45 × 10<sup>−7</sup> to 9 _._ 28 × 10<sup>−4</sup> ppb for OH, 8 _._ 04 × 10<sup>−8</sup> to 0.036 ppb for HO2, 3 _._ 06 × 10<sup>−13</sup> to 5.71 ppb for NO, 1 _._ 15×10<sup>−3</sup> to 17.9 ppb for NO2, 4.9 to 84.7 ppb for O3, 1 _._ 85×10<sup>−8</sup> to 1 _._ 71×10<sup>−3</sup> ppb for NO3, 0 to 0.39 solar intensity (as a fraction of full sun), and 227 to 315<sup>◦</sup> _𝐾_ . The full GEOS-Chem dataset was far too large to use directly for PSO, so we represented it using the k-means clustering algorithm to create six clusters representative of the full sample. The full dataset and k-means cluster data are available in the supporting files. We ran a 50×80 optimization on the AMORE 1.1 mechanism and a 50×50 optimization on the AMORE v1.2 mechanism with the respective original mechanisms as seed particles. Table 6.4 shows the results of these runs, along with the fitness values of the original AMORE mechanisms and the PSO mechanisms from the prior testing conditions. The mechanisms optimized under prior testing conditions did not perform well under the new GEOSChem derived conditions, however, the newly optimized mechanisms had improved performance over the AMORE baseline mechanisms. The standard deviations increased by a modest amount, suggesting that a subset of the conditions in the dataset may have been poorly represented by the clustered data. Further investigation showed that most of the high error results were in conditions with OH concentrations less than 10<sup>−5</sup> ppb, suggesting that this range was not as well represented in the clusters, or in the original conditions used. We tested these new mechanisms on the original conditions in Table 8.2.1 and obtained errors of 0.32 for the AMORE v1.1 PSO and 0.26 for the AMORE v1.2 PSO, which is better than the original mechanism values shown in Table 6.4. These results demonstrate that PSO can be used effectively to optimize mechanisms in a diverse set of conditions, including in ones that span the atmospheric condition space.

## **6.5 Conclusion**

In this paper, we present an optimization approach for obtaining the optimal parameters of a reduced isoprene mechanism, such that the fidelity to the full mechanism is maximized. The approach relies on the popular and effective evolutionary optimization algorithm, particle swarm

131



<!-- Start of picture text -->
—©—Reference Mechanism<br>—*— AMORE v1.2<br>—&— AMORE v1.2 PSO Optimized<br>3.5 ene 1 —~ 0.06<br>s f:<br>3 Py if<br>& 2% 2 06) 17 § © ig<br>215) k 5x 0.4 lB|B =z 0.03}?fi :<br>=i wi ~ 5 02<br>05 0.2 tis twa Fy 0.01}<br>00—P2 0: :<br>05 10 15 20 0 5 10 15 20 0 5 10 15 20<br>Model Time (hrs) Model Time (hrs) Model Time (hrs)<br>—~1.5 0.25; £<br>2 =~ ~ ri<br>g go,& sins 2 02;44<br>> 1 fad 0.1579<br>: : Jos @ 011<br>0.59% = ‘<br>3 0.05<br>000<br>05 10 15 20 0 5 10 15 20 0 5 10 15 20<br>Model Time (hrs) Model Time (hrs) Model Time (hrs)<br><!-- End of picture text -->



<!-- Start of picture text -->
Bias from Reference Value for Different Species under Varying Conditions for AMORE v1.1<br>Sample 1 - High OH Sample 2 - High OH & NO Sample3 - High O3<br>Mmm AMORE v1.1 Mmm AMORE v1.1 Mmmm AMORE v1.1<br>Mm Stoich + Rate 1.75 Mam Stoich + Rate 0.6 Mm Stoich + Rate<br>4 @@™ Only Stoich @@—™ Only Stoich @@™ Only Stoich<br>1.50 0.5<br>3 1.25 0.4<br>v 1.00 0.3<br>22<br>© 0.75<br>> 0.2<br>Co) 0.50<br>Yi<br>5 0.25 0.1<br>a<br>o)<br>‘5 0 0.00 0.0<br>- Sample 4 - High NO3 Sample 5 - High NO3 & no hv Sample 6 - High Isoprene<br>€ @@m AMORE v1.1 Mm AMORE v1.1 8 @@m AMORE v1.1<br>° 0.4 l@m™ Stoich + Rate Mmm Stoich + Rate lm Stoich + Rate<br>D @@™ Only Stoich 0.4 @@—™ Only Stoich 7 @@™ Only Stoich<br>& 6<br>iva] 0.3 03<br>5<br>0.2 0.2 4<br>3<br>0.1 0.1 2<br>1<br>0.0°OH HO, NO NO, HCHOIEPOX. °° GH HO, NO NO, HCHOIEPOX.  ° OH HO, NO NO, HCHO EPOX<br><!-- End of picture text -->

##### Bias from Reference Value for Different Species under Varying Conditions for AMORE v1.2



<!-- Start of picture text -->
Sample 1 - High OH Sample 2 - High OH & NO Sample3 - High O3<br>1.6 mmm AMORE v1.2 2.5 Mmm AMORE v1.2 mmm AMORE v1.2<br>1.4 mM mm StoichStoich + Rate mM mm StoichStoich + Rate | 1.2) mmmMill StoichStoich + Rate<br>12 2.0 1.0<br>1.0 15 0.8<br>$s 0.8 0.6<br>© 0.6 1.0<br>3 0.4<br>2 0.4 0.5<br>MO 0.2 0.2<br>a<br>fod)<br>‘oD 0.0 0.0 0.0<br>- Sample 4 - High NO3 Sample 5 - High NO3 & no hv Sample 6 - High Isoprene<br>€ 0.40 mmm AMORE v1.2 Mmm AMORE V1.2 | 4 9 mmm AMORE v1.2<br>° Mmm Stoich + Rate 0.40 Mmm Stoich + Rate | lm Stoich + Rate<br>w= 0.35 mm Stoich mm Stoich 3.5 lm Stoich<br>-=a 0.30 0.35 .<br>a 0.30 3.0<br>0.25<br>0.25 2.5<br>0.20 0.20 2.0<br>0.15 0.15 1.5<br>0.10 0.10 1.0<br>0.05 0.05 0.5<br>0.00 0.00 0.0<br>OH HO, NO NOz HCHO IEPOX OH HO, NO  NOz HCHO IEPOX OH HO, NO  NO2z HCHO IEPOX<br><!-- End of picture text -->

optimization (PSO). We have discussed the results for optimization of only stoichiometric coefficients, and that of stoichiometric coefficients and rate constants simultaneously. The latter results in a larger search space due to additional objective variables to be optimized, which PSO is able to handle reasonably well.

The benefits accrued from the optimization of parameters of a reduced mechanism are its increased accuracy when compared to the complete large-scale mechanism. Such an optimized reduced mechanism can be used independently for making predictions of the concentrations of important species in the atmosphere, for a fraction of the computational power in comparison to the full reference mechanism. While the parameters obtained are not globally optimum, the approach yields optimal parameter values for both the reduced mechanisms considered in this article, with an improvement by up to 28.8% in the objective function (for the conditions shown in Table 8.2.1) over the baseline state-of-the-art mechanism. Our results are specific to the reduced isoprene models tested and our objective function. However, the PSO method has potential to be applied to other reduced models with differing constraints and optimization goals, as the method is flexible to using any objective function and mechanism. Here we have demonstrated that PSO is a viable method for optimizing reduced isoprene mechanisms using box model simulations with useful levels of improvement in a reasonable time-frame using widely available software tools and modest computational resources.

## **Open Research Section**

The MATLAB and python scripts and mechanism result data for running the PSO algorithm and measuring mechanism performance in this study are available on Github (https://github.com/fcw2110/GAPSO-AMORE) via 10.5281/zenodo.14210944 with open access [138]. This repository contains the scripts needed to run the PSO algorithm in Matlab, along with ancillary scripts for running and testing mechanisms. Data is also provided for the performance of the mechanisms demonstrated in this work, along with the mechanism files.

This publication was developed under Assistance Agreement No. 84001301 awarded by the

135

U.S. Environmental Protection Agency to McNeill. The views expressed in this article are those of the authors and do not necessarily represent the views or policies of the U.S. Environmental Protection Agency. EPA does not endorse any products or commercial services mentioned in this publication. VV is grateful for support in part by the NSF EFRI-DCheM 2132142 grant and funding from the Center for the Management of Systemic Risk (CMSR) at Columbia University.

136

# **Chapter 7: Artificially Intelligent Mechanism Reduction for Gas-phase**

# **Isoprene Oxidation**

## **7.1 Introduction**

In this chapter, we describe a fully-automated approach for mechanism reduction, where we combine an artificially intelligent (AI) genetic algorithm with domain-knowledge, resulting in a hybrid AI [122] approach to automated mechanism reduction. Here we demonstrate this prescriptive approach on isoprene oxidation chemistry. One can choose to adapt the principles described in this text for their respective domains, and can thus implement a fully-automated strategy for mechanism reduction.

Genetic algorithms employ and search strategy, and the potential search space for such the problem at hand exceeds the order of 10<sup>300</sup> mechanisms (more than Chess and Go, combined when we consider 25 reactions in the reduced mechanism, and a maximum of 12 products per reaction). However, in practice it must be noted that many of these potential mechanisms would be invalid, since they would not adhere to mechanistic laws, _e.g.,_ species balance in reactions. Further, since the reduced mechanism is for the process of isoprene oxidation, it is imperative that the reactions occurring be originating from isoprene through some interaction – whether direct or indirect. Accordingly, we formulate the problem of finding a reduced mechanism for the gas-phase oxidation of isoprene, as a search problem subject to mechanistic constraints imposed, within this exceedingly large search space.

In this section, we have stated the objective of this research article, and presented a literature review of previous efforts in mechanism reduction. In Section 7.2 we discuss the techniques applied, and the domain knowledge infused, into the automated mechanism reduction algorithm. Consequently, we present the results in Section 7.3. We discuss the different types of reduced

137

mechanisms obtained from the entirely automated algorithm, and the differences in their connectivity to the existing benchmarks. Lastly, in Section 7.4 we summarize our approach, and provide additional avenues that future research may choose to explore.

## **7.2 Methods**

We present an overall strategy for automatically obtaining reduced mechanisms of the gasphase isoprene oxidation process. The algorithm takes user-defined information at the start, which corresponds to the expert knowledge included in the AI approach. This includes – but is not limited to – bounds on the number of reactions, the possible species involved in each of the reactions, rate laws for specific types of reactions, and the type of reactions that are permitted. Our method, termed as **G** enetic **A** lgorithmic - **A** utomated **Mo** del **Re** duction (GA-AMORE), relies on searching through a combinatorially large space of potential mechanisms, through the application of genetic algorithm (GA) [139]. The search is aided through the inclusion of domain knowledge, allowing for only those reduced mechanisms which satisfy the imposed mechanistic constraints.

The the overall mechanism reduction framework is a two-step procedure: first, reduced mechanisms are generated and tested for their fitness iteratively (in accordance with the GA) followed by the genetic operations; second, the best performing mechanisms are optimized using particle swarm optimization (PSO) to obtain the optimal stoichiometric parameters such that the fitness score is minimized. This results in reduced mechanisms that are feasible, and explainable by a human expert (as ensured by the constraints), while also being highly accurate, as a result of the subsequent stoichiometric parameter optimization.

In the following sections, we discuss the GA, and its modifications which have permitted us to obtain relevant reduced mechanisms from such a large search space. We discuss a two-step procedure within the GA such that we can obtain mechanisms which are considered feasible by a human expert. This has been described in greater detail in the discussion of the fitness function. Next, we present the pre-specified knowledge that was provided to the algorithm, and the constraints imposed on the same, such that the mechanisms generated were not in violation of

138

any first-principles. Lastly, we discuss the stoichiometric parameter optimization, which leads to fine-tuning of the best reduced mechanisms obtained after the GA has concluded.

## 7.2.1 Genetic Algorithm (GA)

GA is a popular stochastic evolutionary optimization algorithm which has been applied to a myriad of different problems, ranging from in-silico molecular discovery [128], mathematical model discovery [123, 124], mechanistic models for process systems engineering [127, 126], zeolite structure-property relationship [125], among numerous other applications [140]. Here, a set of potential candidates (termed as _individuals_ ) are generated, and assigned a score ( _fitness_ ) based on a user-defined function. In this work, each individual is a reduced mechanism that has been generated based on the selection from pre-specified reactants, products, and reaction types. The fitness function is analogous to a loss-function in ML regression exercises, and can be tailor-made for a particular task. Here, we tune the fitness function such that specific reactants and reaction types are preferred over others. This enables a guided search by the GA, and results in mechanisms which are adherent.

The individuals are then ranked on the basis of their fitness, followed by a series of _genetic_ operations which alters the individuals, resulting in a modified set of individuals. In literature pertaining to evolutionary algorithms, a collection of individuals is termed as _population_ . These steps are repeated for a pre-specified number of iterations ( _generations_ ), or until a desired threshold of the fitness value is achieved (can be set at the start of the GA). This is depicted in Figure 7.1.

The need for using evolutionary algorithms in GA-AMORE are two-fold. First, due to the colossal search space of potential reduced mechanisms, it is not possible to feasibly perform an exhaustive search. Hence, a greedy approach such as GA provides us the opportunity to search effectively on the basis of its inherent exploratory nature. This is further aided by the genetic operations, which allow exploration, while also carrying forward the best performing individuals to the subsequent generations. Second, the need for an evolutionary algorithm (here, PSO) for the stoichiometric parameter optimization stemmed from the fact that it is an effective derivative-free

139



<!-- Start of picture text -->
CALTECH Full Mechanism<br>Reduced Mechanism<br>. INO, + HO, — IPN + OH INO, + HO, — IPN + OH<br>OH + ISOPN > CO + NO. Md IHN — HNO, THN HNOs<br>? on vs. ISOPOOH — MGLY + CH;CO;<br>INO, + HO, > IPN + OH ISOPOOH — MGLY + CH,CO, eee<br>IHN — HNO; 22 reactions<br>Os +1 . 1,500 reactions<br>ISOPOOH > MGLY + CH,CO,<br>y<br>° 4Individual i | Generation j Fitness Score f;u<br>Genetic Operations<br>1. Selection<br>2. Replace reaction ,<br>3. Replace product(s) ‘ Chr)? (Sc emma eo<br>4. Generate new mechanism INO, + HO, > IPN + OH<br>IHN — HNO,<br>O03 +1<br>%<br>On ISOPOOH — MGLY + CH,CO,<br>%<br>2)<br>On, *.<br>28,s ° Individual é | Generation j y<br><!-- End of picture text -->

optimization technique, since the fitness function is a non-parametric function that yields a scalar output when provided with a candidate reduced mechanism.

## 7.2.2 Fitness function

The GA-AMORE reduced mechanisms were created in two steps, requiring two different fitness functions. The first step used the genetic algorithm to generate a mechanism structure without optimization of stoichiometric coefficients. The second step used the particle swarm optimization (PSO) to choose optimal stoichiometric coefficients for the mechanism structure that was generated. The first step required faster fitness calculations to make up for the large search space, whereas the second step required a high fidelity fitness function to ensure that the final mechanism had high accuracy. The high fidelity fitness function required a 0-D box model chemical mechanism solver, which solved the ordinary differential equations (ODEs) of the mechanism for a given set of conditions. This calculation is relatively slow, and puts a limit on the number of mechanisms that can be tested within a reasonable time-frame. For this reason, a rapid but lower fidelity fitness function was developed for the genetic algorithm. This fast fitness function did not require an ODE solver, and instead relied on quick estimations of mechanism properties based solely on the structure of the mechanism.

The ultimate goal of the reduced isoprene mechanism is to emulate the production and consumption of key priority species within the mechanism and related atmospheric background species. Both fitness functions averaged the performance of the test mechanism against a reference mechanism across multiple important species and multiple initial conditions. Thus, a large number of performance data points were amalgamated to create the fitness output.

The development of a mechanism structure with the Genetic Algorithm involved determining the reactants and products of the mechanism, with rules put in place to limit the number of valid reactions. All of the stoichiometric coefficients were set to a default value of 1 to further reduce the search space. The fitness function compared the yields of key species in the GA generated structural mechanism to the yields of the full isoprene mechanism. These yields were calculated

141

using the rapid yield algorithm (RYA) developed in Wiser et al. [53] and expanded upon in this work.

The RYA works by apportioning mass flux through all species in the mechanism based on set initial condition. In the case of the isoprene mechanism, isoprene is a source for all further species in the mechanism, and all yields are derived from isoprene. The rapid yield algorithm functions by simplifying mechanisms into graphs. Reactant species and product species are connected by graph edges. One limitation of the graph representation is that there is no simple way to represent reactions with two reactants, as such reactions would require a hyperedge, rather than a standard edge. In the case of the isoprene mechanism (and the atmospheric oxidation of other organic compounds), the second reactants are either highly reactive small molecules, or organic radicals which can be classified into categories. By assuming those secondary reactants have a constant concentration, they can be excluded from the graph representation, eliminating the need for hyperedges in this context. In practice, these species do not have constant concentration, but rather than accounting for that within the yield algorithm, it can be accounted for by estimating yields under multiple different concentrations of these species.

With the mechanism graph constructed, mass flux is apportioned through the graph from the root species downward to all connecting species. For a directed acyclic graph (DAG), mass flows in one direction, from parent species to child species through the mechanism until species without any outgoing connections are reached. In this type of graph, the mass is given by Equation 7.1.



Here, _𝑌𝐴_ represents the yield of species A, the set of all species is given by _𝑁_ , _𝑒𝑛𝐴_ is the edge weighting going from species _𝑛_ to species _𝑎_ . This calculation is dependent on already knowing the yield of species _𝑛_ , thus the yields must be calculated in an order such that the yields of all parents species must be calculated before the yield of a given species is calculated. This is accomplished by ordering species using a topological ordering [95] for the species and calculating yields in that order.

142

Most mechanism graph are not directed acyclic graphs and contain some number of strongly connected components (SCCs). In these subsets of the graph, there is no clear parent/child relationship between species as they are both reachable from one another. Thus no topological ordering of these graphs can be made. To circumvent this, the yields within the SCC are calculated using a separate method. Using these yields, the SCC is represented as a DAG sub-component by connecting all SCC species with external incoming connections to all outgoing connections from the SCC and removing any edges connecting species within the SCC.

The yields from within the SCC are calculated for each SCC species that as an incoming connection from outside of the SCC. This species is assigned a mass of one, and mass is apportioned using the weighted edges of the graph. The mass is distributed using an iterative method, where mass flows from all species which currently contain mass proportionally to their outgoing edges. After multiple iterations, some fraction of the mass will be outside of the SCC and some will remain within it. Using linear extrapolation, the amount of mass that will eventually reach each outgoing species is calculated. The directed acyclic edge connecting an SCC species to an outgoing species is given by Equation 7.2.



Here _𝐶_<sup>_𝑖_</sup> _𝐴_<sup>is the current mass of species A at iteration</sup><sup>_𝑖_, found by summing the edges connecting</sup> to _𝐴_ of all species within the _𝑠𝑐𝑐_ multiplied by their mass at the prior iteration. _𝑌𝐴_<sup>∗</sup><sup>_𝑖_represents</sup> the cumulative mass (yield) of A at iteration i, _𝛼_<sup>_𝑖_</sup> is the fraction of original mass that remains in the SCC at iteration i, _𝑡_ is the last iteration. _𝛼_<sup>_𝑖_</sup> is used to linearly extrapolate the final cumulative

143

mass _𝑌𝑎_<sup>∗of species</sup><sup>_𝐴_, which becomes the directed acyclic edge</sup><sup>_𝑒𝑛𝐴_where ∗indicates that cyclical</sup> elements have been removed. With the conversion of all SCC components to DAG components, Equation 7.1 can be used for all species. The benefit of this method is that it greatly speeds up the calculation of species yields from the mechanism (over an order of magnitude) compared to an ODE solver, allowing for faster exploration of the search space for the GA.

Using the RYA, yields can be estimated for all species within a mechanism given concentrations of all secondary reactants and the needed parameters to calculate reaction rate constants (temperature, pressure, and solar intensity). This algorithm is approximately six times faster than the corresponding box model ODE solver. It took approximately 1.54 seconds to measure an individual mechanism, and 31 seconds to measure an entire 20 mechanism population for one generation on a Dell 2000 MHz Inspiron 15 8-core laptop with 16 GB RAM. The fitness function was calculated by using an importance weighted average of the yields of all key species compared to the full reference mechanism across multiple samples of possible secondary reactant concentrations. Equations 7.3-7.5 show how the fitness function was calculated.







Here, _𝑌𝑛,𝑥_<sup>+/−</sup> is either the total production + or consumption − of species _𝑛_ under condition _𝑥_ , _𝛾_ is a yield threshold, _𝜈𝑛,𝑥_<sup>+/−istheproduction(+)orconsumption(−)scoreforspecies</sup><sup>_𝑛_under</sup> condition _𝑥_ , _𝛼𝑛_<sup>−is a binary value determining whether consumption should be taken into account</sup> for species _𝑛_ , _𝑓_ ( _𝑛, 𝑥,𝑇, 𝑅_ ) is the single species _𝑠_ score under condition _𝑥_ using test mechanism T and reference mechanism R, _𝜔𝑥_ is a weighting for condition _𝑥_ , _𝜔𝑛_ is a weighting for species

144

_𝑛_ , and _𝐹_ ( _𝑇, 𝑅_ ) is the overall score for test mechanism _𝑇_ compared to reference mechanism _𝑅_ . This mechanism fitness function ranges from 0 to 1 (assuming normalized weightings), where 0 indicates a perfectly matching mechanism structure and 1 indicates complete divergence from the full mechanism.

One observed issue was the capacity for this fitness function to promote mechanisms containing non-mass-conserving cycles. This lead to mechanisms which create substantial amounts of mass, prohibiting them from adequately matching the reference mechanism. To counteract this, we added an additional filter to the fitness function to give a large score to any mechanism with a non-mass conserving cycle by identifying any species yields higher than a set threshold (10 mol/mol isoprene in this case). This was able to minimize any mass conservation issues in the resulting mechanisms.

Once a structural mechanism was generated from the GA process, stoichiometric coefficients were optimized using PSO with a new fitness function. This fitness function required higher fidelity than the first, and designed to be a final pass before the mechanism was ready for use. The fitness function utilized the Framework for 0-D Atmospheric Modeling (F0AM) box model (citation) running in MATLAB® [141]. Similarly to the prior fitness function, this fitness function compared the key species between the test mechanism and full mechanism using an importance weighted average over multiple samples. However, in contrast to the first fitness function, the species were compared on the basis of a ODE solver of the chemical equations, at the cost of a higher run time. The following equation was used to define the error of a candidate mechanism:







145



Here, _𝑥_ represents an input condition; _𝑠_ represents the measured species; _𝑇_ denotes the test mechanism; _𝑅_ denotes the reference mechanism; _𝑝𝑥,𝑠_<sup>_𝑀_(</sup><sup>_𝑡_) and</sup><sup>_𝑐_</sup> _𝑥,𝑠_<sup>_𝑀_(</sup><sup>_𝑡_) represent the rate of production</sup> and consumption respectively for species _𝑠_ with input conditions _𝑥_ using mechanism _𝑀_ ; _𝛼𝑠_ denotes whether consumption should be taken into account for species _𝑠_ ; _𝐶𝑥,𝑠_<sup>_𝑀_and</sup><sup>_𝑃_</sup> _𝑥,𝑠_<sup>_𝑀_represent the total</sup> net consumption and production of species _𝑠_ with input conditions _𝑥_ for mechanism _𝑇_ over the total run time from _𝑡_ 0 to _𝑡 𝑓_ ; _𝑓𝑥,𝑠_ ( _𝑇, 𝑅_ ) represents the performance for an individual species; _𝜔𝑠_ is the weighting for species s; and _𝐹_ ( _𝑇, 𝑅_ ) is the overall mechanism error metric. Each _𝑓_ value ranges from 0 to 1, with 0 indicating perfect matching and 1 indicating infinite divergence. The overall mechanism score function _𝐹_ is also normalized from 0 to 1.

The samples chosen for this function were also highly influential on the final output, however, the criteria for sample selection was slightly different. Whereas in the first phase, samples with strong preference for certain mechanistic pathways were selected, in this sample set, samples were chosen to represent different atmospherically relevant conditions. The conditions used for this evaluation function are given in Table A3.

## 7.2.3 Domain knowledge inclusion into GA

In GA-AMORE – since the objective was to obtain a reduced mechanism of the gas-phase isoprene oxidation – it was imperative to have reduced mechanisms which were connected to isoprene ( _𝐼𝑆𝑂𝑃_ ) as the starting point, since all other products were derivatives from the reaction(s) of _𝐼𝑆𝑂𝑃_ reacting with species already present in the atmosphere. This reduced the number of mechanisms that existed in the search space. While this may seem trivial, it is possible to obtain reduced mechanisms which are not connected to _𝐼𝑆𝑂𝑃_ (depicted in Figure 7.2). This may result in a higher fitness, but infeasible mechanisms, since in reality such a system would not be possible. Thus, the inclusion of such a constraint benefited the search, and resulted in more mechanistically feasible reduced mechanisms.

146



<!-- Start of picture text -->
ies Ze<br>BRD<br><!-- End of picture text -->



<!-- Start of picture text -->
Selection Replace reaction<br>@) lf »<br>OH + ISOPN > CO + NO, OH + ISOPN — CO, + NO3 OH +ISOPN — CO + NO, INO, + HO, — IPN + OH<br>IHN — HNO, IHN — HNO, IHN — HNO, IHN — HNO,<br>ISOPOOH —> MGLY + CH,CO, ISOPOOH > MGLY + CH,CO, ISOPOOH > MGLY + CH,CO,, ISOPOOH — MGLY + CH,CO,<br>Individual 1 | Generation 29 Individual 1 | Generation 30 Individual 17 | Generation 29 Individual 17 | Generation 30<br>Replace product(s) Create new mechanism<br>(c) (a) a<br>OH + ISOPN — |CO + NO,| OH + ISOPN — | CO, + NO,| OH + ISOPN — CO + NO, INO, + HO, > IPN + OH<br>IHN > HNO; IHN > HNO, IHN — HNO, OH + IPC — MACP<br>ISOPOOH > MGLY + CH,CO, ISOPOOH > MGLY + CH,CO, ISOPOOH > MGLY + CH,CO,, HO2 + ISOPOOH — IEPOX<br>Individual 10 | Generation 29 Individual 10 | Generation 30 Individual 15 | Generation 29 Individual 15 | Generation 30<br><!-- End of picture text -->

## **Selection**

This genetic operation selects a user-defined number of the best performing individuals from the entire population (set of candidate mechanisms). In that generation, no further genetic operations will be performed on these individuals – they will proceed to the next generation, without any changes, and their fitness values will be re-evaluated

## **New Reaction Mutation**

In this genetic operation a reaction is randomly chosen from a mechanism, and is substituted with a new reaction. This includes changes in the reactants and products, and the corresponding rate law.

## **New Products Mutation**

Here a reaction is randomly chosen from a mechanism, and its products are substituted with another set of products. At the start of the GA, user provides the maximum number of products that can generated for this genetic operation.

## **New Mechanism Mutation**

This genetic operation enables exploration into into the uninvestigated search-space of potential mechanisms, by replacing a randomly chosen entire mechanism, with a new mechanism. The reactions of this newly generated mechanism conform to the constraints discussed previously in Sections 7.2.3 and 7.2.3. The previously discussed genetic operators (Sections 7.2.3 & 7.2.3) are analogous to _local exploitation_ , since the variations are not as substantial from their predecessors. A new mechanism mutation enables _global exploration_ , since it is expected to add an appreciable amount of _stochasticity_ to the search. This genetic operator provides newer candidates for genetic operations in each generation, or can get eliminated entirely if the fitness score is not high enough to be selected.

149

## 7.2.4 Parameter Optimization

At this stage it must be noted that when the GA generates its reactions, the stoichiometric coefficients are fixed to 1 _._ 0, and the rate parameters are set to the default values as specified in Table 7.1. Accordingly, there is scope for improvement in fitness by modifying these parameters. Thus, we perform parameter optimization on these selected individuals. This corresponds to obtaining better estimates for the stoichiometric coefficients, such that the fitness is improved.

We use the evolutionary algorithm, particle swarm optimization (PSO) [98]. We impose constraints on these parameters on the basis of heuristics, for their bounds. A lower limit of 0 _._ 01 and an upper limit of 2 was chosen for stoichiometric coefficients. This is done to limit the optimization search, and yield mechanistically reasonable stoichiometric coefficients.

## **7.3 Results and Discussion**

The GA-AMORE algorithm was to generate a reduced isoprene mechanism to emulate the full Caltech Isoprene Mechanism [16] with AMORE updates [53]. First, multiple runs were conducted to determine the optimal generation size and number of test mechanisms undergoing each mutation type. We found that a generation size of 20 was ideal, with the 4 best test mechanisms selected without change, 8 mechanisms where one reaction reactant was changed and 8 mechanisms where one reaction products were changed. We omitted the new mechanism mutation, since it was determined that a fully random new mechanism was unlikely to produce a competitive score. The algorithm sought to reduce the mechanism score over the course of the run. Figure 7.4 shows the minimum population score over the course of 500 generations for five identical runs. There is variation in the final score, but each run shows a significant reduction in score.

These candidate mechanisms were then optimized using PSO. Each candidate mechanism achieved at least moderate overall performance after optimization, but there was considerable variation between mechanisms and there was not a strong correlation between the GA optimization score and the final PSO mechanism fitness. This is to be expected, as the GA score does not reflect

150



<!-- Start of picture text -->
180<br>160<br>140<br>120<br>2<br>©<br>@ 100<br>80<br>60<br>40<br>0 100 200 300 400 500<br>Generation<br><!-- End of picture text -->

the overall mechanism fitness, but rather the potential attributed to the mechanism structure. The best performing mechanism after one round of PSO was re-optimized several times using PSO, attaining a final mechanism fitness of 0.245, compared to a fitness of 0.265 for the AMORE 1.2 mechanism, which was a similar size. Thus, the GA-AMORE algorithm was successful at producing a mechanism which exceeded the performance of the current state-of-the-art mechanism.

The mechanism fitness represents an aggregation of performance values from multiple species and conditions. Figure 7.5 shows the bias in net production yield between the candidate mechanism and the reference full mechanism. Similar data for other well-performing GA mechanisms is shown in Figure A1. For the select set of species, which are among the most important species for the isoprene mechanism, the GA-AMORE mechanism shows significantly reduced bias.

In addition, select concentration plots for formaldehyde (HCHO), isoprene epoxy-diol (IEPOX), and methacrolein (MACR) are given in Figure 7.6. The net yield of each species is similar among mechanisms. For high O3 conditions, the GA-AMORE mechanism has divergent concentration contours due to the faster rate of reaction in these conditions compared to the reference mechanism. However, the yield of the key species remains very similar to the reference mechanism.

Figure 7.7 shows the graph structure of the best GA-AMORE mechanism (b) compared to the AMORE v1.2 mechanism (a), along with two other well-performing GA-AMORE mechanisms (c,d). Given that the GA optimization process does not consider the chemical formula of intermediates, the intermediates do not have full mechanism analogues and are given representative names instead (‘ISO1’, ‘ISO2’, etc.). It was observed that several reactions in the GA-AMORE mechanism did not contribute significantly to the overall mass flux, and the resulting edges are colored in black, compared to the red edges which had significant contribution. In addition, one intermediate species (‘ISO4’), was observed to have no outgoing reactions, thus making it a mass sink, for visual clarity it was removed from this graph visualization.

The selection of concentrations of secondary reactants had a strong influence on the resulting mechanisms. We found that the inclusion of conditions in which only one secondary reactant had a non-zero concentration was essential for eliminating non-existent pathways. In addition, assigning

152



Figure 7.5: Comparison of bias in net yield of a select set of key isoprene derived species between the best GA-AMORE isoprene mechanism (orange) and the AMORE v1.2 isoprene mechanism (blue).

153



<!-- Start of picture text -->
5.0<br>=> High OH High O3 High NO3<br>o.<br>&<br>oO 25<br>L<br>— 0.0<br>— 02<br>ia)<br>a<br>a<br>Se 0.1<br>o<br>LUoO =<br>= 0.0<br>— 20<br>a — full mech<br>— — AMORE<br>r 1.0<br>O — GA<br>< nn ——<br>— 0.0<br>0 24 48 7? O 24 48 f2 0 24 48 T2<br>Hours Hours Hours<br><!-- End of picture text -->

values of zero to under emphasized secondary reactants allowed for the isolation of the mechanistic pathway being highlighted by a given condition. The complete set of conditions used for our optimizations can be found in Table 8.2.1. The selection of the concentrations of secondary reactants was one aspect in which domain knowledge was highly important for the development of a desirable mechanism. The case of the isoprene mechanism, it is widely known that isoprene initially reacts with either the hydroxyl radical, ozone, or _𝑁𝑂_ 3, to form second generation isoprene species. These first three reactions are the basis of the isoprene mechanism. While the GA approach is less likely to create reactions that match one for one to the reference mechanism or other reduced mechanisms due to its stochastic nature, some level of resemblance to existing isoprene mechanisms is desirable. Thus, a selection of concentration samples which guided the algorithm towards the inclusion of these key reactions was employed. The simplest method for doing so was to create samples in which the target secondary species ( _𝑂𝐻_ , _𝑂_ 3, _𝑁𝑂_ 3) had a nonzero concentration, and all other possible reactants had no concentration. While these concentrations are not atmospherically relevant, they serve to force the algorithm to choose reactions with the select species, or else have no yields at all under those conditions.

These three samples alone were enough to ensure the inclusion of reactions between isoprene and _𝑂𝐻_ , _𝑂_ 3, and _𝑁𝑂_ 3, however this alone was not enough to create a sufficient mechanism, as other reactants ( _𝐻𝑂_ 2, _𝑁𝑂_ , and organic radicals) play a key role in the isoprene mechanism. Thus, a larger sample set ( _𝑁_ = 18) was included, wherein each sample was designed to highlight a certain mechanistic pathway. Table A2 shows each sample included in the GA process.

The GA-AMORE isoprene mechanism and the AMORE v1.2 isoprene mechanism both contain reactions of isoprene with OH, O3, and NO3, to produce intermediates and end products. This is sensible, given that these reactions are in the full isoprene mechanism as well. The remaining chemistry differs between the two mechanisms, although both contain a reversible reaction involving the intermediary product of the reaction of isoprene with OH (ISOPOO and ISO1). As such, each end product species is regulated primarily by a small set of reactions. For example, the production of NO2, a key ozone regulator, is produced primarily by the reaction of ISO1 with

155

NO which is in direct competition with ISO1 HO2. ISO1 is produced primarily by the reaction of isoprene with OH. This simple scheme, with calibrated parameters, is able to accurately capture the production of NO2, as shown in Figure 7.5.

## **7.4 Conclusions and Future Work**

We have presented an automated framework for the reduction of a large chemical reaction mechanism, to a smaller (order of magnitude reduction of 100x) and tractable mechanism, by use of domain knowledge-driven genetic algorithm. Further, numerical optimization of the stoichiometric parameters for the obtained reduced mechanisms was performed using bounded particle swarm optimization. Such an approach yielded several satisfactory mechanisms, which are comparable to the state-of-art mechanisms for the particular example presented in this article – gas-phase oxidation of isoprene. The automated framework is not specific to the example discussed, and can be adapted to other applications, subject to the availability of relevant domain knowledge.

While it is possible to obtain the structure of a reduced mechanism, and simultaneously optimize its stoichiometric parameters, such an approach with the current fitness function would be computationally very expensive. It is our hope that within the next decade, such an approach would enable one to greedily obtain a better performing mechanism than the ones we have highlighted in this text.

## **7.5 Additional Tables**

156



<!-- Start of picture text -->
ISOP<br>NO3<br>ISO2<br>O3<br>ISOP<br>OH, O3 OH, O3 ISO5<br>OH NO3<br>O3 O3 O3<br>ISOPOO NO3 INO2 ISO3<br>CH3CO3 MO2 OH<br>O3 OH HO2 NO NO<br>ISO1 O3 CH3CO3<br>ISOPOOH IHN CH3CO3<br>CH3CO3 Out<br>Out<br>ISO6<br>a) b)<br>ISOP<br>OH, O3<br>ISOP<br>ISO1 NO3<br>NO3<br>O3, MO2 NO<br>NO3 ISO6 O3, OH<br>O3 CH3CO3, NO3 ISO2<br>OH, O3 MO2 NO, MO2, NO2 NO2<br>ISO4 NO O3 O3 ISO2 NO MO2, NO2 ISO4<br>O3 NO3 OH MO2 NO, OH, NO2, NO3 HO2 NO2<br>ISO5 NO, NO2 ISO1 ISO5<br>OH NO3 NO3<br>NO3 ISO6 O3 Out NO2<br>ISO3 Out ISO3<br>c) d)<br><!-- End of picture text -->

Figure 7.7: Graph representations of the best performing GA-AMORE mechanism (b) and the AMORE v1.2 mechanism (a), with two other with GA-AMORE mechanisms (c,d) shown as well. End products represented as Out. The nodes represent species, and the edges represent reactant product pairs within the mechanism. Edge labels represent the background reactant involved in the reaction. Red indicates edges with more significant reaction rates.

157

|Reaction<br>type|First reactant|Second reactant|Reaction rate|
|---|---|---|---|
|_𝑃𝑙𝑎𝑖𝑛_|ISOPOO, ISOPOOH, INO2,<br>IPN,IPC,IHN|N/A|1×10<sup>−5</sup>|
|_𝑃ℎ𝑜𝑡𝑜_|ISOPOO, ISOPOOH, INO2,<br>IPN,IPC,IHN|N/A|_𝑆𝑈𝑁_×10<sup>−5</sup>|
|_𝑂𝐻_|_𝑂𝐻_|ISOP, ISOPOO, ISOPOOH,<br>INO2,IPN,IPC,IHN|1×10<sup>−10</sup>|
|_𝑁𝑂_|_𝑁𝑂_|ISOP, ISOPOO, ISOPOOH,<br>INO2,IPN,IPC,IHN|5×10<sup>−12</sup>_𝑒_<sup>−290/</sup><sup>_𝑇_</sup>|
|_𝑁𝑂_2|_𝑁𝑂_2|ISOP, ISOPOO, ISOPOOH,<br>INO2,IPN,IPC,IHN|9×10<sup>−12</sup>|
|_𝑁𝑂_3|_𝑁𝑂_3|ISOP, ISOPOO, ISOPOOH,<br>INO2,IPN,IPC,IHN|6_._3×10<sup>−13</sup>|
|_𝐻𝑂_2|_𝐻𝑂_2|ISOP, ISOPOO, ISOPOOH,<br>INO2,IPN,IPC,IHN|2_._64×10<sup>−13</sup>_𝑒_<sup>1300/</sup><sup>_𝑇_</sup>|
|_𝑂_3|_𝑂_3|ISOP, ISOPOO, ISOPOOH,<br>INO2,IPN,IPC,IHN|1_._7×10<sup>−17</sup>|
|_𝑂_2|_𝑂_2|ISOP, ISOPOO, ISOPOOH,<br>INO2,IPN,IPC,IHN|1×10<sup>−13</sup>|
|_𝐶𝐻_3_𝑂𝑂_|_𝐶𝐻_3_𝑂𝑂_|ISOP, ISOPOO, ISOPOOH,<br>INO2,IPN,IPC,IHN|1×10<sup>−12</sup>|
|_𝐷𝑜𝑢𝑏𝑙𝑒_|ISOP, ISOPOO, ISOPOOH,<br>INO2,IPN,IPC,IHN|_𝐶𝐻_3_𝐶𝑂_3or_𝐶𝐻_3_𝑂𝑂_|2×10<sup>−12</sup>|



Table 7.1: The different reaction types and reaction rates, along with the first and second reactant. These were specified as the rules on the basis of which the reactions were created by GA-AMORE in a candidate reduced mechanism. SUN refers to a unitless numerical value between 0 to 1 assigned to the strength of the sun’s radiation.

158



<!-- Start of picture text -->
a) b)<br><!-- End of picture text -->

Figure 7.8: Comparison of bias in net yield of a select set of key isoprene derived species between two additional well-forming GA-AMORE isoprene mechanisms (orange in a and b) and the AMORE v1.2 isoprene mechanism (blue).

|Description|OH|NO|NO3|HO2|O3|RO2|Photolysis|
|---|---|---|---|---|---|---|---|
|OH, hv|0.0001|0|0|0|0|0|1|
|OH, NO, hv|0.0001|0.01|0|0|0|0|1|
|OH, NO, HO2, hv|0.0001|0.01|0|0.005|0|0|1|
|OH, HO2, hv|0.0001|0|0|0.005|0|0|1|
|OH, HO2, RO2hv|0.00002|0|0|0.005|0|0.001|1|
|NO3|0|0|0.000325|0|0|0|0|
|NO3, HO2|0|0|0.000325|0.005|0|0|0|
|NO, NO3|0|0.01|0.000325|0|0|0|0|
|NO, NO3, HO2|0|0.01|0.000325|0.005|0|0|0|
|OH, NO, NO3, HO2|0.000002|0.01|0.000325|0.005|0|0|0|
|OH, NO, NO3|0.000002|0.01|0.000325|0|0|0|0|
|OH, NO3, HO2|0.000002|0|0.000325|0.005|0|0|0|
|OH, NO, NO3, HO2, hv|0.000002|0.01|0.000325|0.005|0|0|1|
|O3, hv|0|0|0|0|122|0|1|
|HO2, O3, hv|0|0|0|0.005|122|0|1|
|OH, O3, hv|0.00001|0|0|0|122|0|1|
|OH, HO2, O3, hv|0.00001|0|0|0.005|122|0|1|
|OH, NO, HO2|0.00001|0.01|0|0.005|0|0|0|
|NO, HO2, RO2|0|0.01|0|0.005|0|0.001|0|



Table 7.2: Conditions used for the genetic algorithm to create reduced mechanism structures. All species values are in units of ppb and photolysis is a unitless constant describing the rate of photolytic reactions.

159

|Run Description|ISOP|OH|HO2|NO|O3|NO3|RO2|Photolysis|
|---|---|---|---|---|---|---|---|---|
|High OH|5|0.0002|0.007|0.01|0|0|0.001|1|
|High OH and NO|5|0.0002|0.007|0.2|0|0|0.001|0|
|High O3|2|0.00001|0.007|0.01|100|0|0.001|1|
|High NO3|1|0.00001|0.007|0.1|0|0.0002|0.001|1|
|High NO3no_ℎ𝜈_|1|0.00001|0.007|0.1|0|0.0002|0.001|0|
|High Isop|10|0.0002|0.007|0.02|0|0|0.001|1|



Table 7.3: Six different run conditions used to evaluate mechanisms in the Particle Swarm Optimization. All species values have units of ppb. Photolysis is a unitless constant.

160

# **Chapter 8: Graph Theory Assisted Gradient Descent Optimization of**

# **Reduced Mechanisms**

## **8.1 Introduction**

This chapter describes new graph theory-assisted methods for optimization of reduced mechanisms. The Automated MOdel REduction 2.0 (AMORE 2.0) algorithm generates reduced atmospheric chemical mechanisms with no manual work required. The output mechanisms are accurate up to small mechanism sizes, but error increases as mechanism size decreases. All reduction steps of the AMORE 2.0 algorithm are made on a first-principles basis, and the mechanism is not optimized during the reduction. While this approach works well and is efficient, the reduced mechanism is not optimized. In particular, the stoichiometric coefficients of the reduced mechanism are easily modifiable without changing the structure of the mechanism, and there is significant room for improvement upon the initial selection of these parameters by the algorithm, especially at small mechanism sizes. Gradient descent optimization has the capacity to improve stoichiometric coefficients, but it is computationally inefficient. Here, we present several graph theoretic techniques to improve upon gradient descent while making it more efficient, and apply these techniques to AMORE 2.0 isoprene mechanisms reduced from the Caltech Isoprene Mechanism [16].

The efficacy of the optimization is measured by an evaluation function where the score represents how far off the yields of priority species are from the yield in the reference full mechanism, normalized to allow for inter-species comparison and aggregation. In the case of isoprene, the reference full mechanism is the Caltech Isoprene Mechanism [4]. Our reference data is obtained by simulating the results of the full chemical mechanism either on a box model or on our custom built-in yields simulator. Optimizing the coefficients of a reduced mechanism is a complicated task since coefficients are interconnected: an update of one may change the optimal value of another.

161

|Run Description|ISOP|OH|HO2|NO|O3|NO3|RO2|Photolysis|
|---|---|---|---|---|---|---|---|---|
|Standard|1|0.0002|0.007|0.08|20|0.007|0.001|1|
|Low NO_𝑥_|1|0.0002|0.007|0.02|0|0|0|1|
|High NO_𝑥_|1|0.0002|0.007|0.2|0|0|0|1|
|High O3|1|0.0001|0.007|0.03|80|0|0.001|1|
|High NO3Low_ℎ𝜈_|1|0.00005|0.003|0.08|0|0.007|0.001|0|
|Low_ℎ𝜈_|1|0.00005|0.003|0.08|20|0|0.001|0|



Table 8.1: Six different run conditions used to evaluate mechanisms. All species values have units of ppb. Photolysis is a unitless constant.

Additionally, though the model is reduced, simulating it is computationally intensive, requiring the evaluation of the model in a variety of atmospheric conditions and assessing the accuracy of each yield. Lastly, there may be tradeoffs in the optimization of specific yields: as one yield gets better, another gets worse.

## **8.2 Methods**

## 8.2.1 Mechanism Evaluation and Data Preparation

## **Mechanism Evaluation**

The isoprene mechanism influences several important atmospheric species, including OH, HO2, NO, NO2, ozone (O3), formaldehyde (HCHO), and isoprene epoxy-diol (IEPOX), lumped isoprene nitrates (ISOPN), lumped tetra functional species (TETRA), lumped bifunctional nitrates (IHN), the methyl radical (CH3OO), the acyl-peroxy radical (CH3CO3), glyoxal (GLY), methylglyoxal (MGLY), methyl vinyl ketone (MVK), and methacrolein (MACR). The mechanism evaluation function includes individual performance metrics for each of the priority species involved in the mechanism, which are given an importance weighting based on the environmental context. In order to take into consideration the performance of the mechanism across multiple species and conditions, the objective function consists of a weighted average of the performance of many species across multiple conditions. The conditions used in this work are given in Table 8.2.1.

The ultimate goal of the reduced mechanism is to produce the same amount of each product as the original full mechanism. Thus, a useful mechanism evaluation function measures how close the

162

yields of all priority products are in the reduced mechanism compared to the full mechanism. In addition, products yields may span orders of magnitude, so a useful metric must also be normalized from 0 to 1, in order to account for different scales between species. The mechanism function used in this work is described in the following equations:







Here, _𝑥_ represents a set of input conditions, _𝑠_ represents the priority species being measured, _𝑇_ denotes that the test mechanism is being measured, _𝑅_ denotes that the reference mechanism is being measured, _𝑝_<sup>_𝑇_</sup> _𝑥,𝑠_<sup>(</sup><sup>_𝑡_) represents the rate of production of species</sup><sup>_𝑠_with input conditions</sup><sup>_𝑥_using</sup> mechanism _𝑇_ , _𝑌𝑥,𝑠_<sup>_𝑇_represent the total yield of species</sup><sup>_𝑠_with input conditions</sup><sup>_𝑥_for mechanism</sup><sup>_𝑇_</sup> over the total run time from _𝑡_ 0 to ∞, thus assuming all reactions have gone to completion, and _𝑓𝑥,𝑠_ ( _𝑇, 𝑅_ ) represents the species-run performance metric. The performance metric ranges from 0 to 1, where 0 represents perfect alignment with the entire mechanism, and 1 represents an infinite deviation from the reference mechanism. Only test mechanisms that represent and match the yield of each species will have a performance metric of 0. Equation 8.4 shows the overall objective function used for a test mechanism.



here, _𝐹_ ( _𝑇, 𝑅_ ) is the mechanism evaluation function for a mechanism T compared to the reference mechanism R, _𝑋_ represents the set of all test conditions, _𝑆_ represents all the priority species being measured, _𝜔𝑠_ represents the weighting assigned to a given species (all 1 in this work), and

163



<!-- Start of picture text -->
OH | 0.06<br>ISOPOO<br>< 1.86<br>02] 0.13 double”<br>OH 1.62<br>‘0.13<br>/ 1.22 OH<br>a OH 0.79 NO / 979<br>4<br>»<br>4.22 CHCHO > Cisorn ><br>08 ‘1.44<br>o\ *<br>‘ A AB_---<br>\ --7<br>\ Ue<br><!-- End of picture text -->

The goal of the optimization is to minimize our multidimensional error function with respect to the stoichiometric product coefficients.

However, not all stoichiometric product coefficients are the same. Some coefficients are limited by mass conservation, and there is no uncertainty in their value, and thus cannot change. These coefficients are identified manually before the optimization. In addition, some stoichiometric coefficients have no measurable impact on the yields of the priority species. In both cases, the stoichiometric coefficient does not need to be included in the optimization, thereby reducing the dimensionality of the problem. Coefficients with negligible impact on priority species yields are identified using the Jacobian of the error function:



here, _𝐽 𝑓_ is the Jacobian, where _𝑓 𝑗_ represents the error function output _𝑗𝑥𝑖_ indicates the input stoichiometric coefficient. Negligible stoichiometric coefficients are ones such that:



here epsilon is a small threshold. Any input _𝑥𝑖_ with no terms greater than _𝜖_ in the Jacobian is considered negligible and will not be optimized. This coefficient filtering significantly reduces the dimensionality of the problem. For example, in one candidate reduced mechanism, out of 2062 total coefficients, only 137 were unconstrained by conservation and had a signficant ( _> 𝜖_ ) impact on one of the error function outputs.

## 8.2.2 Gradient Descent

Gradient descent is a method of optimization typically used in machine learning models.

It requires a measurement of the gradient, meaning that multidimensional problems (problems where there are multiple coefficients being optimized) necessitate that the function being optimized be measured at least once for each dimension. Because our error function has a multidimensional

165

output, a method must be used to combine the dimensions to measure the gradient. We combine all outputs that the stoichiometric coefficient being measured has a significant impact on:



From this, each coefficient has its own error function, which may overlap with the error functions of other coefficients. For standard gradient descent, this produces the same result as combining all outputs of the error function, but provides more diagnostic ability, as each error function is tailored to each coefficient. To measure the gradient, we approximate the partial derivative of each coefficient by perturbing it positively and negatively by 5 ∗ 10<sup>−6</sup> _𝑥_ its initial value, evaluating the error _𝐹𝑥𝑖_ (Equation 8.7) at those perturbed points and then finding the slope using point-slope form. As the approximate partial derivative becomes closer to 0, it is likely that the mechanism error function is approaching a local minimum. Though gradient descent is an effective method for optimization, it is computationally expensive for high-dimensional problems. In our case, the mechanism error function takes a significant amount of time to evaluate, and our optimization is on the order of 100-1000 coefficients, making traditional gradient descent much slower to run. Lastly, by using projective gradient descent (a method where coefficients are projected back upon a minimum or maximum value if they exceed that during optimization), we ensured that no coefficient was allowed to be negative, which would be chemically impossible.

## **Anti-Community Clustering**

The fact that each coefficient only influences some of the outputs is very useful, as it allows us to be more efficient in our use of gradient descent. Here we describe a graph theory-based method to improve the efficiency of the gradient descent method, which we term Anti-Community Clustering (ACC).

For this method, we first use the Jacobian to construct a bipartite graph with coefficients as one class of nodes and error function outputs (conditions × priority species) as the other class of nodes. Edges are defined by the following function:

166



<!-- Start of picture text -->
A B C )<br>NO, NO, OH MGLY<br><!-- End of picture text -->



<!-- Start of picture text -->
1) B Cc D 2) B D<br>Noy NO, OH MGLY Noy Non MGLY<br>3) A = 4)<br><!-- End of picture text -->

Identify all output nodes with the least amount of edges 2) remove the coefficient nodes which are connected to the identified yield nodes 3) Repeat steps 1 and 2 until all coefficient nodes are removed, keeping track of the order in which those nodes are removed. The order that results from this undirected graph sorting is the order in which the coefficients are optimized. Any coefficients removed on the same step are placed in a group together and are optimized in parallel. In Figure 8.3, the resulting order is C, A, B, D where all coefficients were removed on a different step, so none are in the same group.

Unlike independent coefficient sorting, we found the best process to perform gradient descent on groups of undirected graph sorted coefficients was to optimize the group continuously rather than iteratively. This means that we optimized a group of coefficients for the total number of iterations before moving on to doing the same for the next group. Additionally, it is important to note that some coefficients within the same group created by undirected graph sorting may interfere with each other and thus must be evaluated independently, making this method less efficient than independent coefficient sorting. To increase efficiency we let each group of coefficients optimize for up to 500 iterations but moved on to the next group earlier if the function had not been optimized by more than 0.1% in the past 20 iterations.

## **Adaptive Learning Rate**

Gradient descent requires a learning rate to influence how much a coefficient should be updated at each step. A challenge is posed in deciding on that learning rate, as some coefficients are more sensitive to changes than others. To overcome the sensitivity difference of coefficients, we employed the use of an adaptive learning rate. Instead of having a global learning rate that is constant for all coefficients, we created learning rate variables that correspond and adapt to each individual coefficient. We tested three types of adaptive learning rates: learning rate multipliers, AdaGrad [ **adagrad** ], and Adam [ **adam** ]. A learning rate multiplier was the simplest of the three, where the learning rate was multiplied by 1.07x if the coefficient was successfully optimized in the last iteration, or by 0.8x if the coefficient was worsened in the last iteration. We chose these values through

169

manual tuning. We then implemented AdaGrad (adaptive gradient algorithm), which uses the history of past gradients for a given coefficient to influence the learning rate. Lastly, we used Adam (adaptive moment estimate) which builds off of AdaGrad by taking an exponential moving average of gradients and taking into account momentum. Adam has been found to be one of the most effective optimizers for training deep neural networks. For Adam, we tuned its hyperparameters which represent rates of decay through manual testing.













## **8.3 Results**

We tested all of our methods on a mechanism generated from a Beta version of the AMORE 2.0 mechanism. In this mechanism, 137 stoichiometric coefficients were optimized using multiple different methods. Table 8.2 shows the runtime in Python for the optimization along with the improvement in the Python-based error function after the optimization was complete. The results in Table 8.2 demonstrate that our two methods of gradient descent modification offer a way to achieve similar levels of optimization at great efficiency. Specifically, anti-community clustering and standard gradient descent both improved AMORE 2.0 beta by 70.44%, as calculated by the mechanism error function in Python, however anti-community clustering took 1.1 hours, whereas standard gradient descent took 5 hours (Table 8.2). We also see that the inclusion of an adap-

170

tive learning rate greatly improved our results, since the nonadaptive version of anti-community clustering only improved AMORE 2.0 Beta by 64.6%. Though undirected graph sorting was not as successful in optimizing the reduced mechanism as anti-community clustering, it demonstrates another way to get a greatly improved reduced mechanism in a shorter amount of time than standard gradient descent. We also see that the methodical ordering in undirected graph sorting aids in achieving greater optimization, as the randomly sorted coefficients improved the AMORE 2.0 Beta mechanism by 62.13%, as calculated by the mechanism error function in Python, while undirected graph sorting improved the AMORE 2.0 Beta mechanism by 67.83%.

|**Method**|**Time (hours)**|**Improvement (%)**|
|---|---|---|
|Nonadaptive Gradient Descent|1.1|64.60|
|Anti-Community Clusters|1.1|70.23|
|Undirected Graph Sorting|1.5|67.83|
|Random Sort|1.5|62.13|
|Standard Gradient Descent|5.0|70.44|



Table 8.2: Performance of various methods along with the time in hours that each method took. Particle swarm optimization is the fastest method but least effective. Anti-community clustering and standard gradient descent are equally effective, but anti-community clustering takes a quarter of the time.

We compared this optimized AMORE 2.0 beta mechanism, along with another optimized AMORE 2.0 100 species mechanism, to several other reduced isoprene mechanisms in the F0AM box model shown in Figure 8.5. The error score as calculated in the MATLAB box model for the unoptimized AMORE 2.0 Beta was 0.13 and the score for the optimized AMORE 2.0 Beta was 0.081, proving that the mechanisms, though optimized using the Rapid Yield Algorithm still display significant improvement when evaluated in MATLAB.

Despite the highest percentage improvement being for AMORE 2.0 Beta, the overall best error score was for AMORE 100, as the starting error score for AMORE 100, 0.064, was significantly better than AMORE 2.0 Beta, 0.13. In Python, AMORE 100 was improved by 44.9% (Figure 8.5), and the optimized mechanism evaluated in the MATLAB box model had an error score of 0.046. This represents an important advance for reduced chemical mechanisms, as through post-reduction

171



<!-- Start of picture text -->
0.5<br>0.4<br>0.3<br>2<br>fo)<br>B<br>0.2<br>5<br>mn<br>0.1<br>0.0<br>Caltech RACM2 CB6r3. +=AMORE 2.0 AMORE 2.0 AMORE AMORE<br>Reduced Beta Beta + ACC 100 100 + ACC<br>Plus<br>Method<br><!-- End of picture text -->



<!-- Start of picture text -->
08 0.45 0.7 - - . .<br>07 0.4 os poms<br>0.6. os. £<br>0.5 _~ 03 f fj<br>=a2Q 04 2~—a2 02502 j B&B2~—a 04-4os #F# ||<br>J<br>©Oox= 0802 >o= 0.15us | °}0 0.2 5 ' |<br>o4 —©- Full Mechanism —©- Full Mechanism 0.1 —2- Full Mechanism J<br>—*- AMORE 2.0 Beta 0.05 —*- AMORE 2.0 Beta 1 —*- AMORE2.0 Beta<br>~ AMORE 2.0 Beta Optimized 6 AMORE 2.0 Beta Optimized ~®- AMORE 2.0 Beta Optimized<br>0 5 10 15 20 0 5 10 15 20 "0 5 10 15 20<br>Model Time (hrs) Model Time (hrs) Model Time (hrs)<br><!-- End of picture text -->

|Species|Unopt.|GD|ACC|RSC|UGS|
|---|---|---|---|---|---|
|OH|0.11|0.08|0.10|0.10|0.09|
|HO2|0.07|0.04|0.06|0.06|0.04|
|NO|0.10|0.05|0.05|0.05|0.04|
|NO2|0.12|0.07|0.07|0.04|0.06|
|O3|0.56|0.33|0.18|0.17|0.17|
|HCHO|0.05|0.04|0.04|0.06|0.04|
|IEPOX|0.18|0.16|0.16|0.14|0.16|
|MGLY|0.19|0.18|0.18|0.24|0.18|
|GLYX|0.34|0.36|0.36|0.36|0.37|
|CH3CO3|0.15|0.18|0.17|0.30|0.17|
|CH3OO|0.39|0.15|0.17|0.10|0.19|
|MACR|0.27|0.17|0.17|0.07|0.08|
|MVK|0.23|0.07|0.05|0.06|0.04|
|ISOPN|0.33|0.11|0.11|0.33|0.15|
|TETRA|0.33|0.09|0.09|0.06|0.10|
|IHN|0.08|0.06|0.05|0.07|0.04|
|Average|**0.22**|**0.13**|**0.13**|**0.14**|**0.12**|
|Weighted Error|**0.15**|**0.09**|**0.09**|**0.11**|**0.09**|



Table 8.3: Errors for a set of priority species for a 12 species AMORE 2.0 isoprene mechanism after several different methods of optimization, including Standard Gradient Descent (GD), AntiCommunity Clustering (ACC), Undirected Graph Shorting (UGS), and Randomly sorted coefficients (RSC). The un-optimized mechanism is shown for comparison.

174

## **8.4 Discussion**

An optimized mechanism, however, would be rendered almost completely obsolete if the improvement in its average error score was determined by the significant improvement of just a few yields, while other yields got notably worse. For example, if the error score of O3 decreased from 0.29 to 0.001 while the error score of OH increased from 0.20 to 0.30, we would see an average improvement in error scores of almost 40%, despite the optimization actually resulting in predictions that are significantly more unreliable for half of the yields. In looking at the error scores in Table 8.3 of key yields in the AMORE 2.0 12 species mechanism optimized with gradient descent using various methods (ignoring the RSC method, which was a comparison for UGS), we see that all species except glyoxal and the methyl radical (whose changes are minimal) show an improvement in error score, as calculated in the MATLAB box model.

All methods tested resulted in some improvement of the reduced mechanism, but the ACC and UGS methods had the best combination of final performance alongside reduce computational cost, making them the best methods for future optimizations. Through these optimization processes, reduced chemical mechanisms are now able to more closely reflect the behavior of a full mechanism and can be accurate at smaller sizes than was previously achievable by the AMORE 2.0 algorithm.

175

# **Chapter 9: Clustering Algorithms for AMORE 2.0 Input Optimization**

This chapter discusses optimization of the input conditions for the AMORE 2.0 algorithm. One of the key inputs of the AMORE 2.0 algorithm is the selection of atmospheric conditions as inputs to the algorithm. In this chapter, we discuss the use of clustering algorithms to optimize the selection of these input conditions from a large atmospheric dataset, along with other considerations regarding input selection. These conditions include all parameters needed to calculate the relative rate of the mechanism reactions, which includes meteorological parameters such a temperature, pressure, and solar intensity, and also the concentration of secondary reactants. The relative rate is defined as the rate of reaction per unit concentration of the primary reactant. This relies on being able to evaluate the rate constant and having a concentration for the second reactant of the reaction if present. The necessary species concentrations provided depend on the full mechanism. Ideally, a concentration (in ppb) will be provided for all secondary reactants. The user must provide a set of species to be considered as secondary reactants by default, which generally includes OH, HO2, NO, NO2, NO3, O3, the methyl radical, and the acyl-peroxy radical. If these species are present in a reaction, then they will be considered the secondary reactant, regardless of their position in the reaction reactant list (1st or 2nd). If there are two reactants and neither reactant is in this secondary reactant set, then the 2nd species in the reactant list will be assumed to be the secondary reactant, and a concentration should be provided for it. If there is no concentration provided for a secondary reactant, a low default concentration will be assigned to calculate the relative rate of reaction.

As such, concentrations of the most common secondary reactants (listed above) are essential for accurate reduced mechanisms. In addition, most mechanisms contain reactions with organic radicals as the second reactant. In the GECKO-A box model, these species are binned into groups, termed PERO1, PERO2, etc. In the isoprene mechanism, these species are listed explicitly. We recommend running a box model of the full mechanism and taking<sup><u>1</u></sup> 2<sup>the maximum concentration</sup>

176

of any organic radical which is a secondary reactant. These concentration values should be used as input conditions for the algorithm.

Secondary reactant concentrations are generally not constant. For example, NO _𝑥_ concentrations vary significantly by location and time of day. To calculate the relative rate, one concentration must be selected. To work around this limitation, the AMORE 2.0 algorithm accepts multiple input conditions, which will lead to the calculation of multiple relative rates. These multiple rates will be used to construct multiple graphs, which are then averaged together to create a representative graph. So, by providing multiple conditions, the reduced mechanism will be representative of a broader set of conditions.

A simple example involving the species NO and OH would be to provide a high and low NO condition. The two conditions would be: OH: 10<sup>−4</sup> ppb, NO: 0.05 ppb, OH: 5 ∗ 10<sup>−5</sup> , NO: 2 ppb. The first stages of the AMORE 2.0 algorithm, including the calculation of relative rates, species yields, and graph construction, would proceed for both of these conditions. Then, the graph and yields would be averaged over the two conditions and the remainder of the algorithm would proceed with the average value.

For the mechanisms presented in the Chapter 3, we chose to use six input conditions. This was a balance between having broader condition representation and algorithm efficiency, as more conditions increase the runtime. The conditions used are shown in Table 8.2.1. There are two approaches to condition selection. The first is to prioritize one condition per mechanism and create multiple mechanisms for multiple conditions. If this method is chosen, then only one condition should be used for each reduced mechanism. The second approach is to create a broad scope reduced mechanism from multiple conditions.

We have conducted additional investigations into the impact of selecting different numbers of input conditions on the accuracy of the reduced mechanism output. To do this, we utilize 1000 data points from a July 2016 single day global GEOS-Chem run. This dataset was created by selecting data points from this run where isoprene concentrations were higher than 0.1 ppb. It is meant to be a representative selection of the range of atmospheric conditions globally which are relevant to

177

||Isop|OH|HO2|NO|NO2|O3|NO3|Sun|Temp (K)|Air Den|( <sup>_𝑘𝑔_</sup><br>_𝑚_<sup>3)</sup>|
|---|---|---|---|---|---|---|---|---|---|---|---|
|Min.|0.10|2.5*10<sup>−7</sup>|8.0*10<sup>−5</sup>|0|0.001|4.9|1.9*10<sup>−8</sup>|0|227|0.34||
|Max.|111|9.3*10<sup>−4</sup>|3.6*10<sup>−2</sup>|5.7|18|85|1.7*10<sup>−3</sup>|0.39|315|1.3||
|Mean|2.6|8.5*10<sup>−5</sup>|7.3*10<sup>−3</sup>|0.06|0.21|28|3.3*10<sup>−5</sup>|0.011|286|1.0||



Table 9.1: The range of conditions for key atmospheric species and parameters for the GEOSChem data set. All atmospheric species are in units of parts per billion (ppb) and Sun is a unitless measure of the solar intensity relative to the maximum intensity of 1.

isoprene chemistry.

This data set covers a wide range of conditions, summarized in Table 9.1.

While this dataset provides a useful range to test mechanism performance, it is too large and therefore inefficient to use directly in the AMORE 2.0 algorithm. Instead, we compared several methods of data clustering to determine the best method of deriving a small set of representative input conditions from the larger data set. The cluster centers obtained from each method were used as input conditions to the AMORE 2.0 algorithm. We repeated this process for 1, 2, 4, 6, 10, 20, 30, 40, 50 and 100 clusters to determine the impact of increasing the number of clusters on the performance of the resulting reduced mechanisms. For each set of clusters, we ran the AMORE 2.0 algorithm to 53, 43, 33, 28, 22, and 14 species. We measured the performance of each of these reduced mechanisms against the full mechanism under all of the 1000 original data points using the rapid yield algorithm with Equation 14 and comparing the following species: OH, HO2, NO, NO2, NO3, O3, methyl radical, acyl-peroxy radical, isoprene, IEPOX, MVK, formaldehyde, HAC, PAN, GLYC, PYRAC, MGLY, HCOOH, MACR, MPAN, GLYX, HMML. The average performance of all of the reduced mechanisms across all 1000 data points was used to determine the performance of the selected clusters.

Our first method was to use the k-means clustering algorithm [143] to select a set number of clusters from the full dataset. The center of each cluster was used as the representative data point to be input into the AMORE 2.0 algorithm. To do this, we first normalized the data to account for differences in scale between the various dimensions of the data set. The acronym for this method is K-M U.

For our next method, we started by measuring the yield of each priority species under each

178

condition using the Rapid Yield Algorithm. This transformed the dataset from a set of atmospheric conditions to a set of species yields arising from those conditions. We then used the k-means clustering algorithm on the yield data to select a set of clusters. The nearest point to each cluster centroid was selected as the representative data point for the cluster, which was then transformed back to the atmospheric data dimensions to be input into the AMORE 2.0 algorithm.

For the next method, we created a new dataset from which to derive clusters. This dataset was created by choosing a small set of wide ranging values for each parameter and creating a gridded dataset, where each possible combination of parameter values is represented. This dataset was of the same magnitude as the GEOS-Chem dataset. The motivation behind this method was that the GEOS-Chem dataset was expected to have many correlated parameters, such that the full space of possible conditions was not explored. While this is representative of atmospheric conditions, it may be suboptimal for mechanism reduction. So, using this gridded data set, we again transformed the data to the yields of priority species, which we then clustered using both k-means (K-M GY) and spectral clustering (S GY) [144].

Figure 9.1 shows the performance of the four clustering methods. The error of each clustering method changes significantly for different numbers of clusters. From these results, there is no clear superior method, although there are some notable trends. The methods which utilize the k- means yield-based methods tend to have less predictable performance while the k-means of the untransformed dataset and the spectral clustering method both have more consistent performance. The best overall set of clusters was the 2 clusters from the k-means gridded yield method. Overall, there is no clear trend in terms of performance versus number of clusters. This may be due to the method used by the AMORE 2.0 algorithm. In the algorithm, a graph is constructed for each condition, but these graphs are eventually averaged together, limiting the added benefit from each additional input.

Figure 9.2 shows select species concentrations (NO, HO2, and OH) arising from four clusters using the four different methods. Each method selects a unique set of concentrations for each species, leading to differing performance results. There are no clear outliers from this set of

179



<!-- Start of picture text -->
Performance for Four Clustering Methods<br>0.22<br>0.2<br>0.18<br>0.16<br>0.14<br>0.12<br>0 20 40 60 80 100<br>Number of Clusters<br>K-M YU K-M GY K-M U S GY<br>Error<br><!-- End of picture text -->

Figure 9.1: Error vs. number of clusters for the four different clustering methods tested for this work. Lower error signifies more robust clusters.

180



<!-- Start of picture text -->
0 0.1550<br>10°<br>s 10-11 @ |] FH 0.15250.1500<br>z 10? - 0.1475<br>s 8 8<br>oa]& 10 - 3 @ 8 0.1450 fas§<br>& 10-4 °<br>2 10- ry 0.1425<br>1o) 10-° - 0.1400<br>10 -6 0.1375<br>0 0.1350<br>iG) 5 ic) ><br>wn = = =<br>vy V x<br>107? e 0.1550<br>Ad 0.1525<br>ry td) ri) Oo 0.1500<br>& 10°?<br>=5 Ps e 0.1475 ov,,<br>fd ry 6 0.1450 8<br>5 o 3 7)<br>2 10 -3 0.1425<br>fo}<br>° 0.1400<br>0.1375<br>10-4 e 0.1350<br>ic} 5 fo} ><br>wn = = =<br>Ny x x<br>0 o 0.1550<br>oO 0.1525<br>ne}3S 0 0 0.1500.<br>210 -4 e<br>iS5Buv 0 0.14750.1450 8mv<br>gg ’ * r 0.1425<br>10-5 e ri) 0.1400<br>0.1375<br>@ 0 0.1350<br>fc} 5 ic) ><br>wn = = =<br>yv V x<br>Method<br><!-- End of picture text -->

clusters, but the performance does vary significantly, with the K-M GY method having the best performance of 0.134.

Some unexpected, but important, conclusions follow from this work. The first is that there is no clear benefit to adding more input conditions. Thus, the added computational costs resulting from adding a large number of conditions is not worthwhile. In terms of the methods given, while there is no clear best choice, the basic approach of k-means clustering on the data itself has the most predictable behavior. More importantly, additional clusters in this method do not increase the error unpredictably as they do with others. For this reason, the straightforward approach of using k- means clustering to identify centroids of atmospheric data for input into the AMORE 2.0 algorithm is our recommended approach. While there was no clear optimal method, the selection of clusters did have a significant impact, albeit difficult to predict. The worst combination of methodology and number of clusters had an error of 0.21, compared to the best combination of method and number of clusters with an error of 0.13, a near 40% improvement. Given this range, we recommend that the user experiment with different input conditions and use a robust testing method to assess the mechanism performance, as it would be easy to inadvertently select conditions that are suboptimal.

182

# **Chapter 10: Conclusions and Future Work**

For this project, we successfully developed and applied the AMORE 2.0 [52], AMORE 1.0 [13], and GA-AMORE algorithms to mechanism reduction and created a Particle Swarm Optimization [54] and Gradient Descent Optimization feature for mechanism optimization. In addition, we developed a set of error metrics for mechanism testing and analysis. We conducted some initial tests on optimizing the inputs of the AMORE 2.0 algorithm as well. Our AMORE v1.0-1.2 isoprene mechanisms were successfully implemented in the GEOS-Chem [55] and CMAQ [13, 8] chemical transport models and the AMORE v1.2 isoprene mechanism is now the default isoprene mechanism for the CRACMM2 atmospheric model developed by the EPA [8]. In this chapter, we discuss possible future work for the AMORE project, focusing on applying the AMORE 2.0 algorithm. The Rapid Yield Algorithm, which was instrumental in this work, has potential to be applied outside of this work as well.

The AMORE 2.0 algorithm is our most advanced and successful mechanism reduction algorithm to date. This algorithm has the capability to reduce a wide range of atmospheric oxidation mechanisms. So far in this work, we have only applied the AMORE 2.0 algorithm to the isoprene and camphene mechanisms, but there are many more species of interest with usable mechanisms. Concurrent work from our group is being done to reduce an alpha-pinene mechanism. Given this new tool, a sensible approach to generating reduced mechanisms would be to identify a set of the most abundant VOCs, weighted for contribution to secondary organic aerosol, in the atmosphere and identify the most detailed and up to date mechanism for these species. For some species, explicit mechanisms developed using extensive data may exist. For other species, there may not be available full mechanisms, in which case, algorithmic mechanism generators would need to be employed, such as the GECKO-A algorithm. From this, a set of AMORE reduced mechanisms could be created and employed as needed on a case by case basis. A more advanced model could

183

be developed to selectively deploy VOC oxidation mechanisms for various species depending on whether the given species has exceeded a threshold of concentration.

In many cases, mechanism developers include all VOCs in one master mechanism. These master mechanisms sacrifice detail of each individual VOC mechanism in exchange for breadth of coverage and ease of implementation. The largest such mechanism is the Master Chemical Mechanism (MCM) [2] which is used for mechanistic insights but is not employed in CTMs. Reduced master models include the Common Representative Intermediates mechanism [57], which was derived from the MCM, and the EPA’s Community Regional Atmospheric Chemistry Multiphase Mechanism (CRACMM) [7, 8]. Any of these mechanisms have the potential to be reduced further. In contrast to prior reductions, these mechanisms have multiple source species. This is not inherently a problem for the AMORE 2.0 algorithm, but significant consideration must be given in terms of how much to weight each of the source species, as this will significantly impact species prioritization. There may be diminishing returns for the smaller of these mechanisms in terms of accuracy. For example, the CRACMM2 mechanism already features the AMORE v1.2 isoprene mechanism [8], which is already highly reduced. Further reduction of the isoprene mechanism, which has relatively high levels of detail compared to other VOC’s in this CRACMM2 mechanism, would essentially be a parametrization of isoprene chemistry with minimal context dependent variation. Here it is important to reiterate the context dependent deployment of more detailed VOC mechanisms would circumvent this issue, as most most model grid cells would require minimal VOC chemistry, and therefore higher complexity would be allowed where VOC chemistry is required.

Another application of the AMORE 2.0 algorithm is in the comparison and assessment of algorithmic mechanism generators. These mechanism generators, including GECKO-A [36] and MECH-GEN [87], are relatively new, and tend to generate exceedingly large mechanisms with limited to no ability to be used in CTMs. Reducing these mechanisms using the AMORE 2.0 algorithm gives the ability to generate CTM-ready candidate mechanisms which can then be compared to observational data, thereby aiding in the refinement and inter-comparison of these methods.

Another area of focus includes the further improvement of the most essential mechanisms.

184

For example, an update of the isoprene mechanism using the AMORE 2.0 algorithm could be used for the next round of the CRACMM mechanism series. Current work is focusing on the development of an alpha-pinene mechanism. The AMORE gradient descent optimizer could be applied to further improve these reduced mechanisms.

The Rapid Yield Algorithm is a tool that we applied to speed up our measurement of species yields from the mechanism. Currently, it is 6 times faster than the equivalent box model run at measuring species yields. It is a graph theory-based algorithm which can measure species yields without an ordinary differential equation (ODE) solver. As such, the runtime for this method is not governed by the same limitations of ODE solvers. For example, ODE solvers require significantly more iterations for stiff systems in order to accurately calculate reaction rates which are very fast. There is no such limitation for the Rapid Yield Algorithm as mechanism stiffness has no direct impact on the runtime of this algorithm. Conversely, the Rapid Yield Algorithm requires more runtime for mechanisms with more strongly connected components, which is not a factor for ODE solvers.

In addition to the base algorithm, we have also developed techniques to add a time dependent element to the species yields and account for reactions wherein neither reactant can be treated as a secondary reactant. This algorithm works best in cases where background species and reactions are easily distinguishable from the chemistry being studied, which applies to VOC chemistry.

In theory, this algorithm could be integrated into a box model or a CTM specifically for VOC chemistry to model to significantly cut back on chemical run times. To do this, the Rapid Yield Algorithm would be called instead of an ODE solver to immediately calculate the yields of all species from the VOC mechanism, which would then undergo transport. Careful calibration would be necessary to account for transport and timescales, but if successful, this method would significantly reduce the complexity of the chemical solver, allowing for more detailed mechanisms to be employed. To perform reliably, sections of chemistry with a high density of strongly connected components, such as the oxidant cycling reactions, would need to be solved for using a traditional ODE solver to account, as these types of mechanisms are not easily applied to the Rapid Yield

185

## Algorithm.

Overall, there is a considerable amount of future work in the field of mechanism reduction and deployment. Thus far, we have developed usable tools for mechanism reduction and developed a select set of reduced mechanisms. However, much work needs to be done to apply utilize these tools across the full set of useful VOC mechanisms.

186

# **References**

- [1] M. Shrivastava _et al._ , “Recent advances in understanding secondary organic aerosol: Implications for global climate forcing,” _Reviews of Geophysics_ , vol. 55, no. 2, pp. 509–559, 2017. eprint: https://agupubs.onlinelibrary.wiley.com/doi/pdf/10. 1002/2016RG000540.

- [2] M. E. Jenkin, J. C. Young, and A. R. Rickard, “The mcm v3.3.1 degradation scheme for isoprene,” _Atmospheric Chemistry and Physics_ , vol. 15, no. 20, pp. 11 433–11 459, 2015.

- [3] Q. Li, J. Jiang, I. K. Afreh, K. C. Barsanti, and D. R. Cocker III, “Secondary organic aerosol formation from camphene oxidation: Measurements and modeling,” _Atmospheric Chemistry and Physics_ , vol. 22, no. 5, pp. 3131–3147, 2022.

- [4] P. O. Wennberg _et al._ , “Gas-phase reactions of isoprene and its major oxidation products,” _Chemical Reviews_ , vol. 118, no. 7, pp. 3337–3390, 2018, PMID: 29522327. eprint: https://doi.org/10.1021/acs.chemrev.7b00439.

- [5] K. H. Bates and D. J. Jacob, “A new model mechanism for atmospheric oxidation of isoprene: Global effects on oxidants, nitrogen oxides, organic products, and secondary organic aerosol,” _Atmospheric Chemistry and Physics_ , vol. 19, no. 14, pp. 9613–9640, 2019.

- [6] M. Jenkin _et al._ , “The cri v2.2 reduced degradation scheme for isoprene,” _Atmospheric Environment_ , vol. 212, pp. 172–182, 2019.

- [7] H. O. T. Pye _et al._ , “Linking gas, particulate, and toxic endpoints to air emissions in the community regional atmospheric chemistry multiphase mechanism (cracmm) version 1.0,” _Atmospheric Chemistry and Physics Discussions_ , vol. 2022, pp. 1–88, 2022.

- [8] T. N. Skipper _et al._ , “Role of chemical production and depositional losses on formaldehyde in the community regional atmospheric chemistry multiphase mechanism (cracmm),” _Atmospheric Chemistry and Physics_ , vol. 24, no. 22, pp. 12 903–12 924, 2024.

- [9] G. Yarwood, S. Rao, M. Yocke, and G Whitten, “Updates to the carbon bond chemical mechanism: Cb05,” _Final report to the US EPA, RT-0400675_ , vol. 8, p. 13, 2005.

- [10] Z. Wang, F. Couvidat, and K. Sartelet, “Generator of reduced organic aerosol mechanism (genoa v1.0): An automatic generation tool of semi-explicit mechanisms,” _Geoscientific Model Development_ , vol. 15, no. 24, pp. 8957–8982, 2022.

187

- [11] L. Watson, D. Shallcross, S. Utembe, and M. Jenkin, “A common representative intermediates (cri) mechanism for voc degradation. part 2: Gas phase mechanism reduction,” _Atmospheric Environment_ , vol. 42, no. 31, pp. 7196–7204, 2008.

- [12] L. E. Whitehouse, A. S. Tomlin, and M. J. Pilling, “Systematic reduction of complex tropospheric chemical mechanisms, part i: Sensitivity and time-scale analyses,” _Atmospheric Chemistry and Physics_ , vol. 4, no. 7, pp. 2025–2056, 2004.

- [13] F. Wiser _et al._ , “Amore-isoprene v1.0: A new reduced mechanism for gas-phase isoprene oxidation,” _Geoscientific Model Development_ , vol. 16, no. 6, pp. 1801–1821, 2023.

- [14] A. G. Xia, D. V. Michelangeli, and P. A. Makar, “Mechanism reduction for the formation of secondary organic aerosol for integration into a 3-dimensional regional air quality model: -pinene oxidation system,” _Atmospheric Chemistry and Physics_ , vol. 9, no. 13, pp. 4341– 4362, 2009.

- [15] A. Guenther, T. Karl, P. Harley, C. Wiedinmyer, P. I. Palmer, and C. Geron, “Estimates of global terrestrial isoprene emissions using megan (model of emissions of gases and aerosols from nature),” _Atmospheric Chemistry and Physics_ , vol. 6, no. 11, pp. 3181–3210, 2006.

- [16] P. O. Wennberg _et al._ , “Gas-phase reactions of isoprene and its major oxidation products,” _Chemical Reviews_ , vol. 118, no. 7, pp. 3337–3390, 2018, PMID: 29522327. eprint: https://doi.org/10.1021/acs.chemrev.7b00439.

- [17] I. K. Afreh, B. Aumont, M. Camredon, and K. C. Barsanti, “Using gecko-a to derive mechanistic understanding of secondary organic aerosol formation from the ubiquitous but understudied camphene,” _Atmospheric Chemistry and Physics_ , vol. 21, no. 14, pp. 11 467– 11 487, 2021.

- [18] T. D. Sharkey, A. E. Wiberley, and A. R. Donohue, “Isoprene emission from plants: Why and how,” _Annals of Botany_ , vol. 101, no. 1, pp. 5–18, Oct. 2007. eprint: https:// academic.oup.com/aob/article-pdf/101/1/5/207866/mcm240.pdf.

- [19] D. Butler T. M. aand Taraborrelli _et al._ , “Improved simulation of isoprene oxidation chemistry with the echam5/messy chemistry-climate model: Lessons from the gabriel airborne field campaign,” _Atmospheric Chemistry and Physics_ , vol. 8, no. 16, pp. 4529–4546, 2008.

- [20] J. H. Kroll, N. L. Ng, S. M. Murphy, R. C. Flagan, and J. H. Seinfeld, “Secondary organic aerosol formation from isoprene photooxidation,” _Environmental Science & Technology_ , vol. 40, no. 6, pp. 1869–1877, 2006, PMID: 16570610. eprint: https://doi.org/ 10.1021/es0524301.

188

- [21] D. K. Henze and J. H. Seinfeld, “Global secondary organic aerosol from isoprene oxidation,” _Geophysical Research Letters_ , vol. 33, no. 9, 2006. eprint: https://agupubs. onlinelibrary.wiley.com/doi/pdf/10.1029/2006GL025976.

- [22] D. K. Farmer _et al._ , “Response of an aerosol mass spectrometer to organonitrates and organosulfates and implications for atmospheric chemistry,” _Proceedings of the National Academy of Sciences_ , vol. 107, no. 15, pp. 6670–6675, 2010. eprint: https://www. pnas.org/doi/pdf/10.1073/pnas.0912340107.

- [23] J. Liu _et al._ , “Efficient isoprene secondary organic aerosol formation from a non-iepox pathway,” _Environmental Science & Technology_ , vol. 50, no. 18, pp. 9872–9880, 2016, PMID: 27548285. eprint: https://doi.org/10.1021/acs.est.6b01872.

- [24] T.-M. Fu, D. J. Jacob, and C. L. Heald, “Aqueous-phase reactive uptake of dicarbonyls as a source of organic aerosol over eastern north america,” _Atmospheric Environment_ , vol. 43, no. 10, pp. 1814–1822, 2009.

- [25] A. M. Fiore, H. Levy II, and D. A. Jaffe, “North american isoprene influence on intercontinental ozone pollution,” _Atmospheric Chemistry and Physics_ , vol. 11, no. 4, pp. 1697– 1710, 2011.

- [26] J. J. Guo _et al._ , “Average versus high surface ozone levels over the continental usa: Model bias, background influences, and interannual variability,” _Atmospheric Chemistry and Physics_ , vol. 18, no. 16, pp. 12 123–12 140, 2018.

- [27] A. Fiore _et al._ , “Estimating north american background ozone in u.s. surface air with two independent global models: Variability, uncertainties, and recommendations,” _Atmospheric Environment_ , vol. 96, pp. 284–300, 2014.

- [28] A. G. Carlton, C. Wiedinmyer, and J. H. Kroll, “A review of secondary organic aerosol (soa) formation from isoprene,” _Atmospheric Chemistry and Physics_ , vol. 9, no. 14, pp. 4987– 5005, 2009.

- [29] A. M. Fiore _et al._ , “Evaluating the contribution of changes in isoprene emissions to surface ozone trends over the eastern united states,” _Journal of Geophysical Research: Atmospheres_ , vol. 110, no. D12, 2005. eprint: https://agupubs.onlinelibrary. wiley.com/doi/pdf/10.1029/2004JD005485.

- [30] K. H. Bates and D. J. Jacob, “A new model mechanism for atmospheric oxidation of isoprene: Global effects on oxidants, nitrogen oxides, organic products, and secondary organic aerosol,” _Atmospheric Chemistry and Physics_ , vol. 19, no. 14, pp. 9613–9640, 2019.

- [31] W. S. Goliff, W. R. Stockwell, and C. V. Lawson, “The regional atmospheric chemistry mechanism, version 2,” _Atmospheric Environment_ , vol. 68, pp. 174–185, 2013.

189

- [32] C Emery, J Jung, B Koo, and G Yarwood, “Improvements to camx snow cover treatments and carbon bond chemical mechanism for winter ozone,” _Final Report_ , 2015.

- [33] B. Aumont, S. Szopa, and S. Madronich, “Modelling the evolution of organic carbon during its gas-phase tropospheric oxidation: Development of an explicit model based on a self generating approach,” _Atmospheric Chemistry and Physics_ , vol. 5, no. 9, pp. 2497–2517, 2005.

- [34] M. Jenkin _et al._ , “The cri v2.2 reduced degradation scheme for isoprene,” _Atmospheric Environment_ , vol. 212, pp. 172–182, 2019.

- [35] L. E. Hatch _et al._ , “Highly speciated measurements of terpenoids emitted from laboratory and mixed-conifer forest prescribed fires,” _Environmental Science & Technology_ , vol. 53, no. 16, pp. 9418–9428, 2019, PMID: 31318536. eprint: https://doi.org/10. 1021/acs.est.9b02612.

- [36] B. Aumont, S. Szopa, and S. Madronich, “Modelling the evolution of organic carbon during its gas-phase tropospheric oxidation: Development of an explicit model based on a self generating approach,” _Atmospheric Chemistry and Physics_ , vol. 5, no. 9, pp. 2497–2517, 2005.

- [37] L. E. Whitehouse, A. S. Tomlin, and M. J. Pilling, “Systematic reduction of complex tropospheric chemical mechanisms, part i: Sensitivity and time-scale analyses,” _Atmospheric Chemistry and Physics_ , vol. 4, no. 7, pp. 2025–2056, 2004.

- [38] L. E. Whitehouse, A. S. Tomlin, and M. J. Pilling, “Systematic reduction of complex tropospheric chemical mechanisms, part ii: Lumping using a time-scale based approach,” _Atmospheric Chemistry and Physics_ , vol. 4, no. 7, pp. 2057–2081, 2004.

- [39] A. G. Xia, D. V. Michelangeli, and P. A. Makar, “Mechanism reduction for the formation of secondary organic aerosol for integration into a 3-dimensional regional air quality model: -pinene oxidation system,” _Atmospheric Chemistry and Physics_ , vol. 9, no. 13, pp. 4341– 4362, 2009.

- [40] Z. M. Nikolaou, J.-Y. Chen, Y. Proestos, J. Lelieveld, and R. Sander, “Accelerating simulations using redchem_v0.0 for atmospheric chemistry mechanism reduction,” _Geoscientific Model Development_ , vol. 11, no. 8, pp. 3391–3407, 2018.

- [41] O. Sturm, “Advecting superspecies: Reduced order modeling of organic aerosols in lotoseuros using machine learning,” M.S. thesis, Delft Netherlands, 2021.

- [42] M. M. Kelp, D. J. Jacob, H. Lin, and M. P. Sulprizio, “An online-learned neural network chemical solver for stable long-term global simulations of atmospheric chemistry,” _Journal of Advances in Modeling Earth Systems_ , vol. 14, no. 6, e2021MS002926, 2022,

190

e2021MS002926 2021MS002926. eprint: https://agupubs.onlinelibrary. wiley.com/doi/pdf/10.1029/2021MS002926.

- [43] H. Lin _et al._ , “An adaptive auto-reduction solver for speeding up integration of chemical kinetics in atmospheric chemistry models: Implementation and evaluation in the kinetic pre-processor (kpp) version 3.0.0,” _Journal of Advances in Modeling Earth Systems_ , vol. n/a, no. n/a, e2022MS003293, e2022MS003293 2022MS003293. eprint: https:// agupubs.onlinelibrary.wiley.com/doi/pdf/10.1029/2022MS003293.

- [44] J. Wei and J. C. W. Kuo, “Lumping analysis in monomolecular reaction systems. analysis of the exactly lumpable system,” _Industrial & Engineering Chemistry Fundamentals_ , vol. 8, no. 1, pp. 114–123, 1969. eprint: https : / / doi . org / 10 . 1021 / i160029a019.

- [45] A. S. Tomlin, M. J. Pilling, T. Turányi, J. H. Merkin, and J. Brindley, “Mechanism reduction for the oscillatory oxidation of hydrogen: Sensitivity and quasi-steady-state analyses,” _Combustion and Flame_ , vol. 91, no. 2, pp. 107–130, 1992.

- [46] A. S. Tomlin, T. Turányi, and M. J. Pilling, “Chapter 4 mathematical tools for the construction, investigation and reduction of combustion mechanisms,” in _Low-Temperature Combustion and Autoignition_ , ser. Comprehensive Chemical Kinetics, M. Pilling, Ed., vol. 35, Elsevier, 1997, pp. 293–437.

- [47] A. Massias, D. Diamantis, E. Mastorakos, and D. Goussis, “An algorithm for the construction of global reduced mechanisms with csp data,” _Combustion and Flame_ , vol. 117, no. 4, pp. 685–708, 1999.

- [48] T. Lu, Y. Ju, and C. K. Law, “Complex csp for chemistry reduction and analysis,” _Combustion and Flame_ , vol. 126, no. 1, pp. 1445–1455, 2001.

- [49] T. Lu and C. K. Law, “A directed relation graph method for mechanism reduction,” _Proceedings of the Combustion Institute_ , vol. 30, no. 1, pp. 1333–1341, 2005.

- [50] P. Pepiot-Desjardins and H. Pitsch, “An efficient error-propagation-based reduction method for large chemical kinetic mechanisms,” _Combustion and Flame_ , vol. 154, no. 1, pp. 67– 81, 2008.

- [51] W. Sun, Z. Chen, X. Gou, and Y. Ju, “A path flux analysis method for the reduction of detailed chemical kinetic mechanisms,” _Combustion and Flame_ , vol. 157, no. 7, pp. 1298– 1307, 2010.

- [52] F. Wiser _et al._ , “A graph theory-based algorithm for the reduction of atmospheric chemical mechanisms,” _ChemRxiv_ , 2025.

191

- [53] F. Wiser _et al._ , “Amore-isoprene v1. 0: A new reduced mechanism for gas-phase isoprene oxidation,” _Geoscientific Model Development_ , vol. 16, no. 6, pp. 1801–1821, 2023.

- [54] A. Chakraborty, F. Wiser, S. Sen, V. F. McNeill, and V. Venkatasubramanian, “Evolutionary optimization of the reduced gas-phase isoprene oxidation mechanism,”

- [55] B. Yang _et al._ , “Implementation and evaluation of the automated model reduction (amore) version 1.1 isoprene oxidation mechanism in geos-chem,” _Environ. Sci.: Atmos._ , vol. 3, pp. 1820–1833, 12 2023.

- [56] T. N. Skipper _et al._ , “Role of chemical production and depositional losses on formaldehyde in the community regional atmospheric chemistry multiphase mechanism (cracmm),” _Atmospheric Chemistry and Physics_ , vol. 24, no. 22, pp. 12 903–12 924, 2024.

- [57] M. Jenkin, L. Watson, S. Utembe, and D. Shallcross, “A common representative intermediates (cri) mechanism for voc degradation. part 1: Gas phase mechanism development,” _Atmospheric Environment_ , vol. 42, no. 31, pp. 7185–7195, 2008.

- [58] G. Sarwar _et al._ , “A comparison of atmospheric composition using the carbon bond and regional atmospheric chemistry mechanisms,” _Atmospheric Chemistry and Physics_ , vol. 13, no. 19, pp. 9695–9712, 2013.

- [59] G. Yarwood, J. Jung, G. Z. Whitten, G. Heo, J. Mellberg, and M. Estes, “Updates to the carbon bond mechanism for version 6 (cb6),” in _9th Annual CMAS Conference, Chapel Hill, NC_ , 2010, pp. 11–13.

- [60] U.S. EPA Office of Research and Development, _Cmaq_ , version 5.3.3, For up-to-date documentation, source code, and sample run scripts, please clone or download the CMAQ git repository available through GitHub: https://github.com/USEPA/CMAQ, Aug. 2021.

- [61] F. Paulot _et al._ , “Unexpected epoxide formation in the gas-phase photooxidation of isoprene,” _Science_ , vol. 325, no. 5941, pp. 730–733, 2009. eprint: https://science. sciencemag.org/content/325/5941/730.full.pdf.

- [62] A. P. Teng, J. D. Crounse, and P. O. Wennberg, “Isoprene peroxy radical dynamics,” _Journal of the American Chemical Society_ , vol. 139, no. 15, pp. 5367–5377, 2017, PMID: 28398047. eprint: https://doi.org/10.1021/jacs.6b12838.

- [63] R. H. Schwantes _et al._ , “Isoprene no3 oxidation products from the ro2 + ho2 pathway,” _The Journal of Physical Chemistry A_ , vol. 119, no. 40, pp. 10 158–10 171, 2015, PMID: 26335780. eprint: https://doi.org/10.1021/acs.jpca.5b06355.

- [64] A. Muñoz, “Isoprene+no+hydrogen peroxide + oh - gas-phase oxidation - product study,” CEAM, Tech. Rep., 2021, url https://data.eurochamp.org/data-access/chamber-experiments/253203848599-4bc9-a35d-993a77cec7c.

192

- [65] A. Muñoz, “Isoprene+ozone+carbon monoxide + o3 - gas-phase oxidation - product study,” CEAM, Tech. Rep., 2021, url https://data.eurochamp.org/data-access/chamber-experiments/253203848599-4bc9-a35d-993a77cec7c.

- [66] EPA, “Technical support document epa’s 2014 national air toxics assessment,” 2018.

- [67] L. Zhu _et al._ , “Formaldehyde (hcho) as a hazardous air pollutant: Mapping surface air concentrations from satellite and inferring cancer risks in the united states,” _Environmental Science & Technology_ , vol. 51, no. 10, pp. 5650–5657, 2017, PMID: 28441488. eprint: https://doi.org/10.1021/acs.est.7b01356.

- [68] R. D. Scheffe _et al._ , “Hybrid modeling approach to estimate exposures of hazardous air pollutants (haps) for the national air toxics assessment (nata),” _Environmental Science & Technology_ , vol. 50, no. 22, pp. 12 356–12 364, 2016, PMID: 27779870. eprint: https: //doi.org/10.1021/acs.est.6b04752.

- [69] K. R. Travis _et al._ , “Can column formaldehyde observations inform air quality monitoring strategies for ozone and related photochemical oxidants?” _Journal of Geophysical Research: Atmospheres_ , vol. 127, no. 13, e2022JD036638, 2022, e2022JD036638 2022JD036638. eprint: https://agupubs.onlinelibrary.wiley.com/doi/ pdf/10.1029/2022JD036638.

- [70] A. Ratkiewicz and T. N. Truong, “Application of chemical graph theory for automated mechanism generation,” _Journal of Chemical Information and Computer Sciences_ , vol. 43, no. 1, pp. 36–44, 2003, PMID: 12546535. eprint: https://doi.org/10.1021/ ci020297f.

- [71] S. J. Silva, S. M. Burrows, M. J. Evans, and M. Halappanavar, “A graph theoretical intercomparison of atmospheric chemical mechanisms,” _Geophysical Research Letters_ , vol. 48, no. 1, e2020GL090481, 2021, e2020GL090481 2020GL090481. eprint: https://agupubs. onlinelibrary.wiley.com/doi/pdf/10.1029/2020GL090481.

- [72] G. M. Wolfe, M. R. Marvin, S. J. Roberts, K. R. Travis, and J. Liao, “The framework for 0-d atmospheric modeling (f0am) v3.1,” _Geoscientific Model Development_ , vol. 9, no. 9, pp. 3309–3319, 2016.

- [73] K. W. Appel _et al._ , “The community multiscale air quality (cmaq) model versions 5.3 and 5.3.1: System updates and evaluation,” _Geoscientific Model Development_ , vol. 14, no. 5, pp. 2867–2897, 2021.

- [74] A. Torres-Vazquez, J. Pleim, R. Gilliam, and G. Pouliot, “Performance evaluation of the meteorology and air quality conditions from multiscale wrf-cmaq simulations for the long island sound tropospheric ozone study (listos),” _Journal of Geophysical Research: Atmospheres_ , vol. 127, no. 5, e2021JD035890, 2022, e2021JD035890 2021JD035890. eprint:

193

https://agupubs.onlinelibrary.wiley.com/doi/pdf/10.1029/ 2021JD035890.

- [75] T. L. Otte and J. E. Pleim, “The meteorology-chemistry interface processor (mcip) for the cmaq modeling system: Updates through mcipv3.4.1,” _Geoscientific Model Development_ , vol. 3, no. 1, pp. 243–256, 2010.

- [76] K. M. Seltzer _et al._ , “Reactive organic carbon emissions from volatile chemical products,” _Atmospheric Chemistry and Physics_ , vol. 21, no. 6, pp. 5079–5100, 2021.

- [77] J. O. Bash, K. R. Baker, and M. R. Beaver, “Evaluation of improved land use and canopy representation in beis v3.61 with biogenic voc measurements in california,” _Geoscientific Model Development_ , vol. 9, no. 6, pp. 2191–2207, 2016.

- [78] J. E. Pleim, L. Ran, W. Appel, M. W. Shephard, and K. Cady-Pereira, “New bidirectional ammonia flux model in an air quality model coupled with an agricultural model,” _Journal of Advances in Modeling Earth Systems_ , vol. 11, no. 9, pp. 2934–2957, 2019. eprint: https://agupubs.onlinelibrary.wiley.com/doi/pdf/10.1029/ 2019MS001728.

- [79] K. W. Appel, R. C. Gilliam, N. Davis, A. Zubrow, and S. C. Howard, “Overview of the atmospheric model evaluation tool (amet) v1.1 for evaluating meteorological and air quality models,” _Environmental Modelling Software_ , vol. 26, no. 4, pp. 434–443, 2011.

- [80] H. O. T. Pye _et al._ , “Epoxide pathways improve model predictions of isoprene markers and reveal key role of acidity in aerosol formation,” _Environmental Science & Technology_ , vol. 47, no. 19, pp. 11 056–11 064, 2013, PMID: 24024583. eprint: https://doi. org/10.1021/es402106h.

- [81] H. O. T. Pye _et al._ , “On the implications of aerosol liquid water and phase separation for organic aerosol mass,” _Atmospheric Chemistry and Physics_ , vol. 17, no. 1, pp. 343–369, 2017.

- [82] K. Mansouri, C. M. Grulke, R. S. Judson, and A. J. Williams, “Opera models for predicting physicochemical properties and environmental fate endpoints,” _Journal of Cheminformatics_ , vol. 10, no. 1, p. 10, 2018.

- [83] K. T. Vasquez _et al._ , “Rapid hydrolysis of tertiary isoprene nitrate efficiently removes no<sub>x</sub> from the atmosphere,” _Proceedings of the National Academy of Sciences_ , vol. 117, no. 52, pp. 33 011–33 016, 2020. eprint: https://www.pnas.org/doi/ pdf/10.1073/pnas.2017442117.

- [84] E. W. Li, P. O. Sturm, S. J. Silva, V. A. Barber, and C. A. Keller, “Characterizing the speed of chemical cycling in the atmosphere,” _Geophysical Research Letters_ , vol. 52, no. 4,

194

e2024GL111021, 2025, e2024GL111021 2024GL111021. eprint: https://agupubs. onlinelibrary.wiley.com/doi/pdf/10.1029/2024GL111021.

- [85] V. Mann and V. Venkatasubramanian, “Ai-driven hypergraph network of organic chemistry: Network statistics and applications in reaction classification,” _React. Chem. Eng._ , vol. 8, pp. 619–635, 3 2023.

- [86] Z. Wang, F. Couvidat, and K. Sartelet, “Implementation of a parallel reduction algorithm in the generator of reduced organic aerosol mechanisms (genoa v2.0): Application to multiple monoterpene aerosol precursors,” _Journal of Aerosol Science_ , vol. 174, p. 106 248, 2023.

- [87] W. P. L. Carter, J. Jiang, J. J. Orlando, and K. C. Barsanti, “Derivation of atmospheric reaction mechanisms for volatile organic compounds by the saprc mechanism generation system (mechgen),” _EGUsphere_ , vol. 2023, pp. 1–65, 2023.

- [88] J. Kerdouci, B. Picquet-Varrault, and J.-F. Doussin, “Prediction of rate constants for gasphase reactions of nitrate radical with organic compounds: A new structureâactivity relationship,” _ChemPhysChem_ , vol. 11, no. 18, pp. 3909–3920, 2010. eprint: https:// chemistry-europe.onlinelibrary.wiley.com/doi/pdf/10.1002/ cphc.201000673.

- [89] T. B. Nguyen _et al._ , “Overview of the focused isoprene experiment at the california institute of technology (fixcit): Mechanistic chamber studies on the oxidation of biogenic compounds,” _Atmospheric Chemistry and Physics_ , vol. 14, no. 24, pp. 13 531–13 549, 2014.

- [90] N. M. Donahue, S. A. Epstein, S. N. Pandis, and A. L. Robinson, “A two-dimensional volatility basis set: 1. organic-aerosol mixing thermodynamics,” _Atmospheric Chemistry and Physics_ , vol. 11, no. 7, pp. 3303–3318, 2011.

- [91] M. M. Kelp, D. J. Jacob, H. Lin, and M. P. Sulprizio, “An online-learned neural network chemical solver for stable long-term global simulations of atmospheric chemistry,” _Journal of Advances in Modeling Earth Systems_ , vol. 14, no. 6, e2021MS002926, 2022, e2021MS002926 2021MS002926. eprint: https://agupubs.onlinelibrary. wiley.com/doi/pdf/10.1029/2021MS002926.

- [92] P. O. Sturm and A. S. Wexler, “A mass- and energy-conserving framework for using machine learning to speed computations: A photochemistry example,” _Geoscientific Model Development_ , vol. 13, no. 9, pp. 4435–4442, 2020.

- [93] P. Virtanen _et al._ , “SciPy 1.0: Fundamental Algorithms for Scientific Computing in Python,” _Nature Methods_ , vol. 17, pp. 261–272, 2020.

- [94] E. W. Dijkstra, “A note on two problems in connexion with graphs,” in _Edsger Wybe Dijkstra: his life, work, and legacy_ , 2022, pp. 287–290.

195

- [95] B. Haeupler, T. Kavitha, R. Mathew, S. Sen, and R. E. Tarjan, “Incremental cycle detection, topological ordering, and strong component maintenance,” _ACM Trans. Algorithms_ , vol. 8, no. 1, Jan. 2012.

- [96] P. V. Leo Törnqvist and Y. O. Vartia, “How should relative changes be measured?” _The American Statistician_ , vol. 39, no. 1, pp. 43–46, 1985. eprint: https://doi.org/10. 1080/00031305.1985.10479385.

- [97] B. Yang _et al._ , “Implementation and evaluation of the automated model reduction (amore) version 1.1 isoprene oxidation mechanism in geos-chem,” _Environ. Sci.: Atmos._ , vol. 3, pp. 1820–1833, 12 2023.

- [98] J. Kennedy and R. Eberhart, “Particle swarm optimization,” in _Proceedings of ICNN’95international conference on neural networks_ , IEEE, vol. 4, 1995, pp. 1942–1948.

- [99] S. Patnaik, X.-S. Yang, and K. Nakamatsu, _Nature-inspired computing and optimization_ . Springer, 2017, vol. 10.

- [100] I. Fister Jr, X.-S. Yang, I. Fister, J. Brest, and D. Fister, “A brief review of nature-inspired algorithms for optimization,” _arXiv preprint arXiv:1307.4186_ , 2013.

- [101] H. Wang, C. Sun, O. Haidn, A. Aliya, C. Manfletti, and N. Slavinskaya, “A joint hydrogen and syngas chemical kinetic model optimized by particle swarm optimization,” _Fuel_ , vol. 332, p. 125 945, 2023.

- [102] C. O. Ourique, E. C. Biscaia, and J. C. Pinto, “The use of particle swarm optimization for dynamical analysis in chemical processes,” _Computers Chemical Engineering_ , vol. 26, no. 12, pp. 1783–1793, 2002.

- [103] M. Schwaab, E. C. Biscaia, Jr., J. L. Monteiro, and J. C. Pinto, “Nonlinear parameter estimation through particle swarm optimization,” _Chemical Engineering Science_ , vol. 63, no. 6, pp. 1542–1552, 2008.

- [104] Y. Zhou, C. Zhao, and X. Liu, “An iteratively adaptive particle swarm optimization approach for solving chemical dynamic optimization problems,” _CIESC J._ , vol. 65, no. 4, pp. 1296–1302, 2014.

- [105] C. O. Ourique, E. C. Biscaia, and J. C. Pinto, “The use of particle swarm optimization for dynamical analysis in chemical processes,” _Computers Chemical Engineering_ , vol. 26, no. 12, pp. 1783–1793, 2002.

- [106] V. Mann, A. Sivaram, L. Das, and V. Venkatasubramanian, “Robust and efficient swarm communication topologies for hostile environments,” _Swarm and Evolutionary Computation_ , vol. 62, no. 100848, 2021.

196

- [107] Y. Wang _et al._ , “A method based on improved ant lion optimization and support vector regression for remaining useful life estimation of lithium-ion batteries,” _Energy Science & Engineering_ , vol. 7, no. 6, pp. 2797–2813, 2019. eprint: https://onlinelibrary. wiley.com/doi/pdf/10.1002/ese3.460.

- [108] S. Alam, G. Dobbie, Y. S. Koh, P. Riddle, and S. Ur Rehman, “Research on particle swarm optimization based clustering: A systematic review of literature and techniques,” _Swarm and Evolutionary Computation_ , vol. 17, pp. 1–13, 2014.

- [109] J.-R. Zhang, J. Zhang, T.-M. Lok, and M. R. Lyu, “A hybrid particle swarm optimization–backpropagation algorithm for feedforward neural network training,” _Applied Mathematics and Computation_ , vol. 185, no. 2, pp. 1026–1037, 2007, Special Issue on Intelligent Computing Theory and Methodology.

- [110] E. Camci, D. R. Kripalani, L. Ma, E. Kayacan, and M. A. Khanesar, “An aerial robot for rice farm quality inspection with type-2 fuzzy neural networks tuned by particle swarm optimization-sliding mode control hybrid algorithm,” _Swarm and Evolutionary Computation_ , vol. 41, pp. 1–8, 2018.

- [111] A. El-Zonkoly, “Optimal placement of multi-distributed generation units including different load models using particle swarm optimization,” _Swarm and Evolutionary Computation_ , vol. 1, no. 1, pp. 50–59, 2011.

- [112] N. Jin and Y. Rahmat-Samii, “Analysis and particle swarm optimization of correlator antenna arrays for radio astronomy applications,” _IEEE Transactions on Antennas and Propagation_ , vol. 56, no. 5, pp. 1269–1279, 2008.

- [113] T. Navalertporn and N. V. Afzulpurkar, “Optimization of tile manufacturing process using particle swarm optimization,” _Swarm and Evolutionary Computation_ , vol. 1, no. 2, pp. 97– 109, 2011.

- [114] M. Pluhacek, R. Senkerik, A. Viktorin, T. Kadavy, and I. Zelinka, “A review of real-world applications of particle swarm optimization algorithm,” Jan. 2018, pp. 115–122, ISBN: 978-3-319-69813-7.

- [115] H. Tong _et al._ , “Hydroxyl radicals from secondary organic aerosol decomposition in water,” _Atmospheric Chemistry and Physics_ , vol. 16, no. 3, pp. 1761– 1771, 2016.

- [116] D. Ma, S. Wang, and Z. Zhang, “Hybrid algorithm of minimum relative entropy-particle swarm optimization with adjustment parameters for gas source term identification in atmosphere,” _Atmospheric Environment_ , vol. 94, pp. 637–646, 2014.

197

- [117] J. Wang, R. Zhang, Y. Yan, X. Dong, and J. M. Li, “Locating hazardous gas leaks in the atmosphere via modified genetic, mcmc and particle swarm optimization algorithms,” _Atmospheric Environment_ , vol. 157, pp. 27–37, 2017.

- [118] D. Ma _et al._ , “Application and improvement of swarm intelligence optimization algorithm in gas emission source identification in atmosphere,” _Journal of Loss Prevention in the Process Industries_ , vol. 56, pp. 262–271, 2018.

- [119] J. Zhang _et al._ , “Support vector machine modeling using particle swarm optimization approach for the retrieval of atmospheric ammonia concentrations,” _Environmental Modeling Assessment_ , vol. 21, Aug. 2016.

- [120] G. N. Kouziokas, “Svm kernel based on particle swarm optimized vector and bayesian optimized svm in atmospheric particulate matter forecasting,” _Applied Soft Computing_ , vol. 93, p. 106 410, 2020.

- [121] Y. Yuan, H.-L. Yi, Y. Shuai, F.-Q. Wang, and H.-P. Tan, “Inverse problem for particle size distributions of atmospheric aerosols using stochastic particle swarm optimization,” _Journal of Quantitative Spectroscopy and Radiative Transfer_ , vol. 111, no. 14, pp. 2106– 2114, 2010.

- [122] A. Chakraborty, S. Serneels, H. Claussen, and V. Venkatasubramanian, “Hybrid ai models in chemical engineering–a purpose-driven perspective,” _Computer Aided Chemical Engineering_ , vol. 51, pp. 1507–1512, 2022.

- [123] A. Chakraborty, A. Sivaram, L. Samavedham, and V. Venkatasubramanian, “Mechanism discovery and model identification using genetic feature extraction and statistical testing,” _Computers & Chemical Engineering_ , vol. 140, p. 106 900, 2020.

- [124] A. Chakraborty, A. Sivaram, and V. Venkatasubramanian, “Ai-darwin: A first principlesbased model discovery engine using machine learning,” _Computers & Chemical Engineering_ , vol. 154, p. 107 470, 2021.

- [125] A. Chakraborty, A. Gandhi, M. F. Hasan, and V. Venkatasubramanian, “Discovering zeolite adsorption isotherms: A hybrid ai modeling approach,” in _Computer Aided Chemical Engineering_ , vol. 53, Elsevier, 2024, pp. 511–516.

- [126] P. Jul-Rasmussen, A. Chakraborty, V. Venkatasubramanian, X. Liang, and J. K. Huusom, “Identifying first-principles models for bubble column aeration using machine learning,” in _Computer Aided Chemical Engineering_ , vol. 52, Elsevier, 2023, pp. 1089–1094.

- [127] P. Jul-Rasmussen, A. Chakraborty, V. Venkatasubramanian, X. Liang, and J. K. Huusom, “Hybrid ai modeling techniques for pilot scale bubble column aeration: A comparative study,” _Computers & Chemical Engineering_ , p. 108 655, 2024.

198

- [128] V. Venkatasubramanian, K. Chan, and J. M. Caruthers, “Evolutionary design of molecules with desired properties using the genetic algorithm,” _Journal of Chemical Information and Computer Sciences_ , vol. 35, no. 2, pp. 188–195, 1995.

- [129] B. Srinivasan, T. Vo, Y. Zhang, O. Gang, S. Kumar, and V. Venkatasubramanian, “Designing dna-grafted particles that self-assemble into desired crystalline structures using the genetic algorithm,” _Proceedings of the National Academy of Sciences_ , vol. 110, no. 46, pp. 18 431–18 435, 2013.

- [130] J. Fang, W. Liu, L. Chen, S. Lauria, A. Miron, and X. Liu, “A survey of algorithms, applications and trends for particle swarm optimization,” _International Journal of Network Dynamics and Intelligence_ , pp. 24–50, 2023.

- [131] J. C. Bansal, P. Singh, M. Saraswat, A. Verma, S. S. Jadon, and A. Abraham, “Inertia weight strategies in particle swarm optimization,” in _2011 Third world congress on nature and biologically inspired computing_ , IEEE, 2011, pp. 633–640.

- [132] T. M. Inc., _Matlab version: 23.2.0.2391609 (r2023b)_ , Natick, Massachusetts, United States, 2023.

- [133] T. M. Inc., _Optimization toolbox version: 23.2 (r2023b)_ , Natick, Massachusetts, United States, 2023.

- [134] E. Mezura-Montes and C. A. C. Coello, “Constraint-handling in nature-inspired numerical optimization: Past, present and future,” _Swarm and Evolutionary Computation_ , vol. 1, no. 4, pp. 173–194, 2011.

- [135] M. E. H. Pedersen, “Good parameters for particle swarm optimization,” _Hvass Lab., Copenhagen, Denmark, Tech. Rep. HL1001_ , pp. 1551–3203, 2010.

- [136] D. E. Goldberg, K. Deb, and J. H. Clark, “Genetic algorithms, noise, and the sizing of populations,” _Complex systems_ , vol. 6, pp. 333–362, 1991.

- [137] C. Coello, E. Goodman, K. Miettinen, D. Saxena, O. Schütze, and L. Thiele, _Interview: Kalyanmoy deb talks about formation, development and challenges of the emo community, important positions in his career, and issues faced getting his works published_ , 2023.

- [138] F. Wiser and A. Chakraborty, _Fcw2110/ga-pso-amore: Amore_pso_ , Software, version 1.2, 2024.

- [139] J. R. Koza, “Survey of genetic algorithms and genetic programming,” in _Wescon conference record_ , Western Periodicals Company, 1995, pp. 589–594.

- [140] S. Katoch, S. S. Chauhan, and V. Kumar, “A review on genetic algorithm: Past, present, and future,” _Multimedia tools and applications_ , vol. 80, pp. 8091–8126, 2021.

199

- [141] T. M. Inc., _Matlab version: 9.13.0 (r2022b)_ , Natick, Massachusetts, United States, 2022.

- [142] J. E. Fowler, M. A. Kottwitz, N. Trask, and R. Dingreville, “Beyond combinatorial materials science: The 100 prisoners problem,” _Integrating Materials and Manufacturing Innovation_ , vol. 13, no. 1, pp. 83–91, 2024.

- [143] J. A. Hartigan and M. A. Wong, “Algorithm as 136: A k-means clustering algorithm,” _Journal of the Royal Statistical Society. Series C (Applied Statistics)_ , vol. 28, no. 1, pp. 100– 108, 1979.

- [144] A. Ng, M. Jordan, and Y. Weiss, “On spectral clustering: Analysis and an algorithm,” in _Advances in Neural Information Processing Systems_ , T. Dietterich, S. Becker, and Z. Ghahramani, Eds., vol. 14, MIT Press, 2001.

200
