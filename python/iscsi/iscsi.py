#!/usr/bin/env python
# -*- coding: utf-8 -*-
#Author: liyunteng

import sys
import os
import getopt
import json

from libiscsitarget import *
from libiscsivolume import *
from libiscsilun import *
from libiscsisession import *
from libiscsichap import *

class iSCSIArgs:
    def __init__(self):
        self.mode = ''
        self.list_set = False
        self.target_name_set = False
        self.target_name_str = ''
        self.modify_set = False
        self.attr_set = False
        self.attr_str = ''
        self.value_set = False
        self.value_set = ''
        self.add_set = False
        self.remove_set = False
        self.remove_set = ''
        self.name_set = False
        self.name_set = ''
        self.detail_set = False
        self.detail_str = ''
        self.udv_set = False
        self.udv_str = ''
        self.blocksize_set = False
        self.blocksize_str = ''
        self.lun_read_only_set = False
        self.lun_read_only_str = ''
        self.read_only_set = False
        self.read_only_str = ''
        self.wrth_str = 'wb'
        self.nv_cache_set = False
        self.nv_cache_str = ''
        self.map_set = False
        self.unmap_set = False
        self.lun_set = False
        self.lun_id_set = False
        self.lun_id_str = ''
        self.initor = '*'
        self.cur_initor = None
        self.fre_initor = None
        self.volume_name_set = False
        self.volume_name_str = ''
        self.udv_set = False
        self.udv_str = ''
        self.force_close_sid = None
        self.get_privilage_set = False
        self.update_cfg = False
        self.restore_cfg = True
        self.default_target = False
        self.chap_user_str = ''
        self.chap_pass_str = ''
        self.chap_set_str = ''
        self.chap_type = ''
        self.chap_dup = False

    def setMode(self, mode):
        if self.mode == '':
            self.mode = mode

def iscsiTargetProc(args = iSCSIArgs()):
    if args.list_set:
        CommOutput(iSCSIGetTargetList(args.target_name_str))
    elif args.modify_set:
        if args.name_str == '':
            comm_exit(False, "请输入被操作的Target名称!")
        elif args.attr_str == '':
            comm_exit(False, "请输入设置的属性名称!")
        elif args.value_str == '':
            comm_exit(False, "请输入设置的属性值!")
        else:
            ret, msg = iSCSISetTargetAttr(args.name_str, args.attr_str, argv.value_str)
            log_insert('NAS', 'Auto', 'Info' if ret else 'Error', msg)
            comm_exit(ret, msg)
    elif args.add_set:
        comm_exit(False, "暂不支持添加Target操作!")
    elif args.remove_set:
        comm_exit(False, "暂不支持删除Target操作!")
    else:
        comm_exit(False, "缺少参数！")
    return

def iscsiAddVolume(args = iSCSIArgs()):
    if not len(args.udv_str):
        comm_exit(False, "请输入UDV名称!")
    try:
        blocksize = 512
        if len(args.blocksize_str):
            blocksize = int(args.blocksize_str)

        read_only = 'disable'
        if len(args.read_only_str):
            read_only = args.read_only_str
    except:
        pass

    return iSCSIVolumeAdd(args.udv_str, blocksize, read_only, args.wrth_str)

def iscsiVolumeProc(args = iSCSIArgs()):
    if args.list_set:
        CommOutput(iSCSIVolumeGetList(args.volume_name_str, args.udv_str))
    elif args.add_set:
        ret, msg = iscsiAddVolume(args)
        log_insert('iSCSI', 'Auto', 'Info' if ret else 'Error', msg)
        comm_exit(ret, msg)
    elif args.remove_set:
        if not len(args.remove_str):
            comm_exit(False, "请设置需要删除的iSCSI数据卷名称!")
        else:
            ret, msg = iSCSIVolumeRemove(args.remove_str)
            log_insert('iSCSI', 'Auto', 'Info' if ret else 'Error', msg)
            comm_exit(ret, msg)
    else:
        comm_exit(False, '缺少参数!')

def iscsiLunProc(args = iSCSIArgs()):
    if args.list_set:
        if len(args.lun_id_str):
            comm_exit(False, "暂不支持获取指定LUN ID信息!")
        CommOutput(iSCSILunGetList(args.target_name_str), dict_dump)

    elif args.map_set:
        if not len(args.target_name_str):
            comm_exit(False, "请输入Target名称!")
        elif not args.add_set and not len(args.volume_name_str):
            comm_exit(False, "请输入iSCSI数据卷名称!")
        elif not len(args.lun_id_str):
            comm_exit(False, "请输入LUN ID")
        elif not len(args.lun_read_only_str):
            comm_exit(False, "请输入读写属性!")

        if args.add_set:
            ret, msg = iscsiAddVolume(args)
            if not ret:
                log_insert('iSCSI', 'Auto', 'Error', msg)
                comm_exit(ret, msg)
            volume_name = getVolumeByUdv(args.udv_str)
            if not volume_name:
                comm_exit(False, "无法获取iSCSI数据卷名称!")
            args.volume_name_str = volume_name

        ret,msg = iSCSILunMap(args.target_name_str, args.volume_name_str,
                args.lun_id_str, args.lun_read_onyl_str, args.initor)
        if ret = False and args.add_set:
            iSCSIVolumeRemove(volume_name)
        log_insert('iSCSI', 'Auto', 'Info' if ret else 'Error', msg)
        comm_exit(ret, msg)

    elif args.modify_set:
        


