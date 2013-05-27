//
//  bsd_structs.h
//  ActivityMonitor++
//
//  Created by st on 26/05/2013.
//  Copyright (c) 2013 st. All rights reserved.
//

#ifndef ActivityMonitor___bsd_structs_h
#define ActivityMonitor___bsd_structs_h

/*
 * We re-define a bunch of varibles and structures which exist in UNIX headers,
 * but are not available on iOS. The returned data types by system calls match
 * these definitions.
 */

// <netinet/tcp_fsm.h>
#define TCPS_CLOSED         0   // Closed.
#define TCPS_LISTEN         1   // Listening for connection.
#define TCPS_SYN_SENT       2   // Active, have sent syn.
#define TCPS_SYN_RECEIVED   3   // Have send and received syn.
// States < TCPS_ESTABLISHED are those where connections not established.
#define TCPS_ESTABLISHED    4   // Established.
#define TCPS_CLOSE_WAIT     5   // rcvd fin, waiting for cose.

char *tcpstates[] = {
    "CLOSED",
    "LISTEN",
    "SYN_SENT",
    "SYN_RCVD",
    "ESTABLISHED",
    "CLOSE_WAIT",
    "FIN_WAIT_1",
    "CLOSING",
    "LAST_ACK",
    "FIN_WAIT_2",
    "TIME_WAIT"
};


// <sys/socketvar.h>
#define XSO_SOCKET  0x001
#define XSO_RCVBUF  0x002
#define XSO_SNDBUF  0x004
#define XSO_STATS   0x008
#define XSO_INPCB   0x010
#define XSO_TCPCB   0x020

#define ALL_XGN_KIND_INP    (XSO_SOCKET | XSO_RCVBUF | XSO_SNDBUF | XSO_STATS | XSO_INPCB)
#define ALL_XGN_KIND_TCP    (ALL_XGN_KIND_INP | XSO_TCPCB)

typedef u_quad_t inp_gen_t;
typedef u_quad_t so_gen_t;

struct xsocket_n {
    u_int32_t   xso_len;    // Length of this structure.
    u_int32_t   xso_kind;   // XSO_SOCKET
    u_int64_t   xso_so;     // Makes a convenient handle.
    short       so_type;
    u_int32_t   so_options;
    short       so_linger;
    short       so_state;
    u_int64_t   so_pcb;     // Another convenient handle.
    int         xso_protocol;
    int         xso_family;
    short       so_qlen;
    short       so_incqlen;
    short       so_qlimit;
    short       so_timeo;
    u_short     so_error;
    pid_t       so_pgid;
    u_int32_t   so_oobmark;
    uid_t       so_uid;     // XXX
};

struct xsockbuf_n {
    u_int32_t   xsb_len;    // Length of this structure.
    u_int32_t   xsb_kind;   // XSO_RCVBUF or XSO_SNDBUF.
    u_int32_t   sb_cc;
    u_int32_t   sb_hiwat;
    u_int32_t   sb_mbcnt;
    u_int32_t   sb_mbmax;
    int32_t     sb_lowat;
    short       sb_flags;
    short       sb_timeo;
};

struct data_stats {
    u_int64_t   rxpackets;
    u_int64_t   rxbytes;
    u_int64_t   txpackets;
    u_int64_t   txbytes;
};

struct xsockstat_n {
    u_int32_t           xst_len;    // Length of this structure.
    u_int32_t           xst_kind;   // XSO_STATS
#define SO_TC_STATS_MAX 4
    struct data_stats   xst_tc_stats[SO_TC_STATS_MAX];
#undef SO_TC_STATS_MAX
};


// <netinet/in_pcb.h>
struct xinpgen {
    u_int32_t   xig_len;    // Length of this structure.
    u_int       xig_count;  // Number of PCBs at this time.
    inp_gen_t   xig_gen;    // Generation count at this time.
    so_gen_t    xig_sogen;  // Socket generation count at this time.
};

struct in_addr_4in6 {
    u_int32_t       ia46_pad32[3];
    struct in_addr  ia46_addr4;
};

struct xinpcb_n {
    u_int32_t   xi_len;     // Length of this structure.
    u_int32_t   xi_kind;    // XSO_INPCB
    u_int64_t   xi_inpp;
    u_short     inp_fport;  // Foreign port.
    u_short     inp_lport;  // Local port.
    u_int64_t   inp_ppcb;   // Pointer to per-protocol PCB.
    inp_gen_t   inp_gencnt; // Generation count of this instance.
    int         inp_flags;  // Generic IP/datagram flags.
    u_int32_t   inp_flow;
    u_char      inp_vflag;
    u_char      inp_ip_ttl; // Time to live.
    u_char      inp_ip_p;   // Protocol.
    union {
        struct  in_addr_4in6    inp46_foreign;
        struct  in6_addr        inp6_foreign;
    } inp_dependfaddr;
    union {
        struct  in_addr_4in6    inp46_local;
        struct  in6_addr        inp6_local;
    } inp_dependladdr;
    struct {
        u_char  inp4_ip_tos; // Type of service.
    } inp_depend4;
    struct {
        u_int8_t    inp6_hlim;
        int         inp6_cksum;
        u_short     inp6_ifindex;
        short       inp6_hops;
    } inp_depend6;
    u_int32_t   inp_flowhash;
};
// These defines are for use with the inpcb.
#define INP_IPV4        0x1
#define INP_IPV6        0x2
#define inp_faddr       inp_dependfaddr.inp46_foreign.ia46_addr4
#define inp_laddr       inp_dependladdr.inp46_local.ia46_addr4
#define inp_route       inp_dependroute.inp4_route
#define inp_ip_tos      inp_depend4.inp4_ip_tos
#define inp_options     inp_depend4.inp4_options
#define inp_moptions    inp_depend4.inp4_moptions
#define in6p_faddr      inp_dependfaddr.inp6_foreign
#define in6p_laddr      inp_dependladdr_inp6_local
#define in6p_route      inp_dependroute.inp6_route
#define in6p_ip6_hlim   inp_depend6.inp6_hlim
#define in6p_hops       inp_depend6.inp6_hops   // Default hop limit.
#define in6p_ip6_nxt    inp_ip_p
#define in6p_flowinfo   inp_flow
#define in6p_vflag      inp_vflag
#define in6p_options    inp_depend6.inp6_options
#define in6p_outputopts inp_depend6.inp6_outputopts
#define in6p_moptions   inp_depend6.inp6_moptions
#define in6p_icmp6filt  inp_depend6.inp6_icmp6filt
#define in6p_cksum      inp_depend6.inp6_cksum
#define in6p_ifindex    inp_depend6.inp6_ifindex
#define in6p_flags      inp_flags       // For KAME src sync over BSD*'s
#define in6p_socket     inp_socket      // For KAME src sync over BSD*'s
#define in6p_lport      inp_lport       // For KAME src sync over BSD*'s
#define in6p_fport      inp_fport       // For KAME src sync over BSD*'s
#define in6p_ppcb       inp_ppcb        // For KAME src sync over BSD*'s
#define in6p_state      inp_state       // For KAME src sync over BSD*'s
#define in6p_wantcnt    inp_wantcnt     // For KAME src sync over BSD*'s
#define in6p_last_outif inp_last_outif  // For KAME src sync over BSD*'s


// <netinet/tcp_var.h>
#define TF_NEEDSYN  0x00400
#define TF_NEEDFIN  0x00800

struct xtcpcb_n {
    u_int32_t       xt_len;
    u_int32_t       xt_kind;                    // XSO_TCPCB
    
    u_int64_t       t_segq;
    int             t_dupacks;                  // Consecutive dup acks recd.
    
#define TCPT_NTIMERS_EXT 4                  // <netinet/tcp_timer.h>
    int             t_timer[TCPT_NTIMERS_EXT];  // TCP timers.
#undef TCPT_NTIMERS_EXT
    
    int             t_state;                    // State of this connection.
    u_int           t_flags;
    
    int             t_force;
    
    tcp_seq         snd_una;                    // Send unacknowledged.
    tcp_seq         snd_max;                    // Highest sequence number sent used to recognize retransmits.
    
    tcp_seq         snd_next;                   // Send next.
    tcp_seq         snd_up;                     // Send urgent pointer.
    
    tcp_seq         snd_wl1;                    // Window update seg seq number.
    tcp_seq         snd_wl2;                    // Window update seg ack number.
    tcp_seq         iss;                        // Initial send sequence number.
    tcp_seq         irs;                        // Initial receive sequence number.
    
    tcp_seq         rcv_nxt;                    // Receive next.
    tcp_seq         rcv_adv;                    // Advertised window.
    u_int32_t       rcv_wnd;                    // Receive window.
    tcp_seq         rcv_up;                     // Receive urgent pointer.
    
    u_int32_t       snd_wnd;                    // Send window.
    u_int32_t       snd_cwnd;                   // Congestion-controlled window.
    u_int32_t       snd_ssthresh;               // snd_cwnd size threshold for slow start exponential to linear switch.
    
    u_int           t_maxopd;                   // mss plus option.
    
    u_int32_t       t_rcvtime;                  // Time at which a packet was received.
    u_int32_t       t_starttime;                // Time connection was established.
    int             t_rtttime;                  // Round trip time.
    tcp_seq         t_rtseq;                    // Sequence number being timed.
    
    int             t_rxtcur;                   // Current retransmit value (ticks).
    u_int           t_maxseg;                   // Maximum segment size.
    int             t_srtt;                     // Smoothed round-trip time.
    int             t_rttvar;                   // Variance in round-trip time.
    
    int             t_rxtshift;                 // log(2) of rexmt exp. backoff.
    u_int           t_rttmin;                   // Minimum rtt allowed.
    u_int32_t       t_rttupdated;               // Number of times rtt sampled.
    u_int32_t       max_sndwnd;                 // Largest window peer has offered.
    
    int             t_softerror;                // Possible error not yet reported.
    // Out-of-band data
    char            t_oobflags;                 // Have some.
    char            t_iobc;                     // Input character.
    u_char          snd_scale;                  // Window scaling for send window.
    u_char          rcv_scale;                  // Window scaling for recv window.
    u_char          request_r_scale;            // Pending window scaling.
    u_char          requested_s_scale;
    u_int32_t       ts_recent;                  // Timestamp echo data.
    
    u_int32_t       ts_recent_age;              // When last updated.
    tcp_seq         last_ack_sent;
    // RFC 1644 variables.
    tcp_cc          cc_send;                    // Send connection count.
    tcp_cc          cc_recv;                    // Receive connection count.
    tcp_seq         snd_recover;                // For use in fast recovery.
    // Experimental.
    u_int32_t       snd_cwnd_prev;              // cwnd prior to retransmit.
    u_int32_t       snd_ssthresh_prev;          // ssthresh prior to rentransmit.
    u_int32_t       t_badrxtwin;                // Window for retransmit recovery.
};

struct xgen_n {
    u_int32_t   xgn_len;    // Length of this structure.
    u_int32_t   xgn_kind;   // Number of PCBs at this time.
};

#endif
