


c = [-50,-40,-30,-20,-10,0,10,20,30,40,50];      
    f = zeros(size(c));
    k = zeros(size(c));
    i=1;
    for i = 1:length(c)
   
    f(i) = (9/5)*c(i)+32;
    k(i) = c(i) + 273.15;
    i = i+1;
    disp(['Celsius: ', num2str(c(i))]);
    disp(['Fahrenheit: ', num2str(f(i))]);
    disp(['Kelvin: ', num2str(k(i))]);

    end
   


   