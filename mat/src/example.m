clear all
close all

load('../dat/100.mat')

t = tm(1:250,:);
s = signal(1:250,1);

imfs = emd(s);

subplot(4,1,1)
plot(t,s,t,emd_filter(imfs,1))
grid on
legend('Original signal', '1 IMF discarded')
ylabel('Amplitude')

subplot(4,1,2)
plot(t,s,t,emd_filter(imfs,2))
grid on
legend('Original signal', '2 IMF discarded')
ylabel('Amplitude')

subplot(4,1,3)
plot(t,s,t,emd_filter(imfs,3))
grid on
legend('Original signal', '3 IMF discarded')
ylabel('Amplitude')
xlabel('Time [s]')

load('cpp.mat')
subplot(4,1,4)
plot(t, s, t, cpp)
grid on
legend('Original signal', '1 IMF discarded')
ylabel('Amplitude')