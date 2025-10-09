%disp(unitstepfunction(-1));
%disp(badunitstep([100,-5,-2,0,1,5,100]));
%disp(betterunitstep([100,-3,-2,-1,0,1,2,3]));
A=rand(5,5);
%B = [-1];
disp(A);
%disp(funcx0(B));
disp(funcx1(A));

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

function x0 = funcx0(t) 
    x0 = size(t);
    x0 = (((t.^2)-1)./((t.^2)+1)).*exp(-(abs(t/10))).*cos(t/(2*pi));
  %  disp(x0);
end

function x1 = funcx1(t)
   x1 = t;
   x1(t<0) = exp(t);
   x1(0<=t<1) = 1;
   x1(t>=1) = exp(1-t);
end