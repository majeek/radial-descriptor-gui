        ��  ��                  .      �� ��e     0 	        29/6/2013
[done]	- add draw descriptorMatrix option
		- add median dominantSet instead of mean option
			- mark chosen vectors in the mean dominant set option

1/7/2013
		- cannot compare partial signatures for now. If bounded box is not drawn the point does not have a complete signature list.

2/7/2013
[done]	- shift descriptor matrix and normalize

4/7/2013
		- to transform the descriptor matrix using fourier-mellin transform before drawing it or not?
5/7/2013
[fixed]	- fixed a huge bug! I never converted the loaded image to grayscale. All prior results were incorrect.

29/7/2013
[done]	- log-polar conversion of a 1d vector is simply log(abs(val)) where val = magI.at(i,j)

31/7/2013
[done]	- got rid of FMT and using |FT| instead. it is shift invariant.
[done]	- add chi square distance
[done]	- add mahalanobi distance

2/8/2013
[done]	- order the different vectors of the dominant set, use labels to find their order.

6/8/2013
[done]	- add option to normalize vectors
[done]	- add option to use first XX values of each vector
  