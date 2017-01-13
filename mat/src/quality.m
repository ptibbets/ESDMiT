clear all
close all

x = 0:0.01:2*pi;
y = sin(x);
yn = y + (rand(size(x)) - 0.5)/5;
rmsen = sum((y - yn).^2)/(length(y));

imfs = emd(yn');

yy = emd_filter(imfs,3);
figure
plot(x,yn,x,yy)
grid on
ylabel('Amplitude')
xlabel('Time [s]')
legend('Noised signal (sin(0:2pi) + rand)', 'Filtered signal - 3 IMF discarded')
rmsef3 = sum((y - yy).^2)/(length(y));

yy = emd_filter(imfs,4);
figure
plot(x,yn,x,yy)
grid on
ylabel('Amplitude')
xlabel('Time [s]')
legend('Noised signal (sin(0:2pi) + rand)', 'Filtered signal - 4 IMF discarded')
rmsef4 = sum((y - yy).^2)/(length(y));

yy = emd_filter(imfs,5);
figure
plot(x,yn,x,yy)
grid on
ylabel('Amplitude')
xlabel('Time [s]')
legend('Noised signal (sin(0:2pi) + rand)', 'Filtered signal - 5 IMF discarded')
rmsef5 = sum((y - yy).^2)/(length(y));
