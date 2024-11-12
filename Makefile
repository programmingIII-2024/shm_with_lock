CC      = gcc
CFLAGS	= -g -O2 -Wall
LDFLAGS = -L/opt/local/lib
LIBS    = -lpthread 

MANAGER_OBJS = ac_manager_l.c
MANAGER_HDRS = 
MANAGER   = ac_manager_l

MONITOR_OBJS = ac_monitor_l.c
MONITOR_HDRS = 
MONITOR   = ac_monitor_l

WITHDRAW_OBJS = ac_withdrawal_l.c
WITHDRAW_HDRS = 
WITHDRAW   =  ac_withdrawal_l

all: $(MANAGER) $(MONITOR) $(WITHDRAW)

$(MANAGER):$(MANAGER_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $(MANAGER_OBJS)

$(MONITOR):$(MONITOR_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $(MONITOR_OBJS)

$(WITHDRAW):$(WITHDRAW_OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $@ $(WITHDRAW_OBJS)

clean:; rm -f *.o $(MANAGER) $(MONITOR) $(WITHDRAW)

