clear all
close all

load('../dat/100.mat')

t = tm(1:250,:);
s = signal(1:250,1);

subplot(3,1,1)
plot(t,s,t,emd_filter(s,1))
grid on
legend('Original signal', '1 IMF discarded')
ylabel('Amplitude')

subplot(3,1,2)
plot(t,s,t,emd_filter(s,2))
grid on
legend('Original signal', '2 IMF discarded')
ylabel('Amplitude')

subplot(3,1,3)
plot(t,s,t,emd_filter(s,3))
grid on
legend('Original signal', '3 IMF discarded')
ylabel('Amplitude')
xlabel('Time [s]')
