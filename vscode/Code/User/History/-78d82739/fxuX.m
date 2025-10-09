%disp(unitstepfunction(-1));
%disp(badunitstep([100,-5,-2,0,1,5,100]));
%disp(betterunitstep([100,-3,-2,-1,0,1,2,3]));
A=rand(5,5);
%B = [-1];
disp(A);
%disp(funcmatrix0(B));
disp(funcmatrix1(A));

function value = unitstepfunction(t) % a not so efficient way of programming a unit step function
   value = (t>=0);
end

function array0 = badunitstep(t)
    for i = 1:length(t)
        array0(i) = (t(i)>=0);
    end
end


function array1 = betterunitstep(t)
    array1 = (t>=0);
end

function matrix0 = funcmatrix0(t) 
    matrix0 = size(t);
    matrix0 = (((t.^2)-1)./((t.^2)+1)).*exp(-(abs(t/10))).*cos(t/(2*pi));
  %  disp(matrix0);
end

function matrix1 = funcmatrix1(t)
   matrix1 = size(t);
   matrix1(t<0) = exp(t);
   matrix1(0<=t<1) = 1;
   matrix1(t>=1) = exp(1-t);
end