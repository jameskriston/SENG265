
function main()
    diary('a2output.txt');
disp('Testing temperature conversion table on values -50C to +50C with steps of 10'); %test and then call my temperature conversion
temperature();
disp(' ');

disp('Testing basic unitstep function on values: -1, 0, 1, 10'); %test basic unitstep function with 4 values and print to screen 


disp(unitstepfunction(-1));
disp(unitstepfunction(0));
disp(unitstepfunction(1));
disp(unitstepfunction(10));

disp('Testing unoptimized unitstep on the array [100,-5,-2,0,1,5,100]'); %test the for loop version of unistep on an array

disp(badunitstep([100,-5,-2,0,1,5,100]));


disp('Testing optimized (2 line) unitstep on the array [100,-5,-2,0,1,5,100]'); %test optimized unistep on same array 
disp(betterunitstep([100,-5,-2,0,1,5,100]));

A = -2 + 4 * rand(3, 3); %generate 3x3 array A with random decimal number between -2 and +2, then print 
disp('This is 3x3 matrix A of numbers between -2 and +2');
disp(A);


disp('Outputting function x0 3.201a) f(t) on matrix A'); %test function x0(t) on array A 
disp(funcx0(A));


disp('Outputting function x1 3.201f f(t) on matrix A' ); % test the piecewise x1(t) on array A
disp(funcx1(A));


end
function value = unitstepfunction(t) % a not so efficient way of programming a unit step function
   value = (t>=0); %returns 1 if >= 0, 0 otherwise
end

function array0 = badunitstep(t) %iterate through array t and check each element >=0, set array0(i) equal to 1 or 0 depending on t(i)>=0
    for i = 1:length(t)
        array0(i) = (t(i)>=0);
    end
end


function array1 = betterunitstep(t) %make new array1 and set all values to either 1 or 0, either element is >=0 and true (1) or <0 and false (0)
    array1 = (t>=0);
end

function x0 = funcx0(t) %disgusting looking equation, perform that long operation on each element of matrix t and set to corresponding element in x0

    x0 = (((t.^2)-1)./((t.^2)+1)).*exp(-(abs(t/10))).*cos(t/(2*pi));
  
end

function x1 = funcx1(t) %piecewise function, make new array of 0s same size as t
   x1 = zeros(size(t));
   x1(t<0) = exp(t(t<0)); %if t<0 then change that value to exp(t)
   x1(t>=0 & t<1) = 1; %for values between 0 and 1 (0 included) change to 1
   x1(t>=1) = exp(1-t(t>=1)); %for values greater or equal to 1, make equal to e^(1-t)
  
end

 function temperature() %simple temperature conversion function
    celsius = -50:10:50;  %make array of Celsius temperatures from -50 to +50 in steps of 10
    farenheit = celsius*(9/5)+32; %calculate farenheit values into farenheit array
    kelvin = celsius + 273.15; %calculate kelvin values into kelvin array

    temptable = table(celsius',farenheit',kelvin', 'VariableNames',{'Celsius','Farenheit','Kelvin'}); %create a 3 column table to store the temperatures
    disp(temptable); %display our table

    
 end %goodnight.
 diary off;