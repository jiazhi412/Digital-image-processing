%Image path
E = 'G:\569\Homework\HW2\Image\Enhanced\12441.jpg'; 
%Ground truth path
[thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( E, "Tiger.mat" );
%compute recall precision F-measure
[R,P,F] = computeRPF(cntR,sumR,cntP,sumP);
%find the best recall precision F-measure
[bstR,bstP,bstF,bstT] = findBestRPF(thrs,R,P);

