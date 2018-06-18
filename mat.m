filename = 'Output.txt';
marr=0;
[marr,delimiterOut]=importdata(filename);
x=marr(:,1);
y=marr(:,2);
plot((x(1:313)),(y(1:313)),'-x')