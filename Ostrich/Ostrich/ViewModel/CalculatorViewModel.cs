using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.Messaging;
using DevExpress.Xpf.Core;
using DevExpress.Xpf.Grid.DragDrop;
using Microsoft.Extensions.DependencyInjection;
using Ostrich.Message;
using Ostrich.Service;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using ViewModel;

namespace Ostrich.ViewModel
{
    public class CalculatorViewModel : ObservableRecipient
    {


        #region PrivateProperty
        private readonly NodeEngineManagerService nodeEngineService;
        private ObservableCollection<ContextViewModel> _ContextViewModelCollection = null;
        private ContextViewModel _SelectedContextViewModel = null;
        private int _ExecutionDelay = 0;
        private bool _IsExecuting = false;

        #endregion


        #region Constructor
        public CalculatorViewModel(NodeEngineManagerService _nodeEngineService) { 
            this.IsActive = true;


            this.nodeEngineService = _nodeEngineService;



            this.ContextViewModelCollection = this.nodeEngineService.ContextViewModelCollection;
        }

        #endregion


        #region Functions


        #endregion


        #region Public Property


        public int ExecutionDelay
        {
            get => _ExecutionDelay;
            set => SetProperty(ref _ExecutionDelay, value);
        }

        public bool IsExecuting
        {
            get => _IsExecuting;
            set => SetProperty(ref _IsExecuting, value);
        }

        public ObservableCollection<ContextViewModel> ContextViewModelCollection
        {
            get => _ContextViewModelCollection;
            set => SetProperty(ref _ContextViewModelCollection, value);
        
        }

        public ContextViewModel SelectedContextViewModel
        {
            get => _SelectedContextViewModel;
            set => SetProperty(ref _SelectedContextViewModel, value);
        }




        #endregion

        #region Command




        public ICommand NodeConnectRequestCommand
        {
            get => new RelayCommand<UC.EventParameter.NodeConnectRequestArg>((arg) =>
            {

                try
                {


                    if (this.IsExecuting == true) return;



                    var contextName = arg.ContextName;
                    var sourceNodeUID = arg.SourceNodeUID;
                    var sourcePropertyName = arg.SourcePropertyName;

                    var targetNodeUID = arg.TargetNodUID;
                    var targetPropertyName = arg.TargetPropertyName;

                    this.nodeEngineService.ConnectNode(contextName, sourceNodeUID, sourcePropertyName, targetNodeUID, targetPropertyName);


                    arg.ConnectComplete = true;

                }
                catch(Exception ex)
                {
                    arg.ConnectComplete = false;

                }

            });
        }


        public IAsyncRelayCommand RunScriptCommand
        {
            get => new AsyncRelayCommand(async () =>
            {

                try
                {
                    System.Diagnostics.Debug.WriteLine("Start");
                    this.IsExecuting = true;
                    await this.nodeEngineService.Run(this.SelectedContextViewModel.Name, this.ExecutionDelay);
                    System.Diagnostics.Debug.WriteLine("End");
                    this.IsExecuting = false;
                }
                catch(Exception e)
                {
                    System.Diagnostics.Debug.WriteLine(e.Message);
                    this.IsExecuting=false;
                }

            });
        }
        public ICommand ContinusRunScriptCommand
        {
            get => new RelayCommand(() =>
            {

                try
                {

                    ///this.nodeEngineService.Run(this.SelectedContextViewModel.Name);

                }
                catch (Exception e)
                {

                }

            });
        }

        public ICommand StopRunScriptCommand
        {
            get => new RelayCommand(() =>
            {

                try
                {

                    ///this.nodeEngineService.Run(this.SelectedContextViewModel.Name);

                }
                catch (Exception e)
                {

                }

            });
        }



        public ICommand NodeConnectivityCheckCommand
        {
            get => new RelayCommand<UC.EventParameter.NodeConnectivityArg>((arg) =>
            {

                try
                {
                    var contextName = arg.ContextName;
                    var sourceNodeUID = arg.SourceNodeUID;
                    var sourcePropertyName = arg.SourcePropertyName;

                    var targetNodeUID = arg.TargetNodUID;
                    var targetPropertyName = arg.TargetPropertyName;

                    arg.CanConnect = this.nodeEngineService.CheckNodeConnectivity(contextName, sourceNodeUID, sourcePropertyName, targetNodeUID, targetPropertyName);
                }
                catch (Exception ex) {

                    arg.CanConnect = false;

                }
            });
        }
        public ICommand DeleteSelectedPathsCommand
        {
            get => new RelayCommand(() =>
            {
                try
                {
                    this.nodeEngineService.DeleteSelectedPaths(this.SelectedContextViewModel.Name);
                }catch(Exception ex)
                {

                }
            });
        }
        public ICommand DeleteSelectedNodesCommand
        {
            get => new RelayCommand(() =>
            {
                try
                {
                    this.nodeEngineService.DeleteSelectedNodes(this.SelectedContextViewModel.Name);
                }catch (Exception ex)
                {


                }
            });
        }

        public ICommand DropNodeCommand
        {
            get => new RelayCommand<DragEventArgs>((args) =>
            {
                try
                {

                    if (this.IsExecuting == true) return;


                    object data = args.Data.GetData(typeof(RecordDragDropData));

                    NodeInfoViewModel viewModel = ((RecordDragDropData)data).Records[0] as NodeInfoViewModel;

                    var position = args.GetPosition(args.Source as IInputElement);

                    System.Diagnostics.Debug.WriteLine(viewModel);
                    System.Diagnostics.Debug.WriteLine("x = " + position.X + " y = " + position.Y);

                    this.nodeEngineService.AddNode(this.SelectedContextViewModel.Name,
                                                   viewModel.ObjectType);

                }
                catch(Exception ex)
                {
                    System.Diagnostics.Debug.WriteLine(ex.ToString());
                }
            });
        }

        public ICommand RenameContextCommand
        {
            get => new RelayCommand(() =>
            {
                try
                {
                    var vm = App.Current.Services.GetService<ContextManageViewModel>();
                    vm.ContextName = "";
                    vm.ConfirmCommand = new RelayCommand(() =>
                    {
                        try
                        {
                            this.nodeEngineService.RenameContext(this.SelectedContextViewModel.Name, vm.ContextName);
                            Messenger.Send<PopupMessage>(new PopupMessage()
                            {
                                IsClose = true
                            });
                        }
                        catch (Exception e)
                        {
                            System.Diagnostics.Debug.WriteLine(e.Message);
                        }

                    });

                    vm.CloseCommand = new RelayCommand(() =>
                    {
                        try
                        {

                            Messenger.Send<PopupMessage>(new PopupMessage()
                            {
                                IsClose = true
                            });
                        }
                        catch (Exception e)
                        {

                        }

                    });

                    Messenger.Send<PopupMessage>(new PopupMessage()
                    {
                        Content = vm,
                        MessageHeight = 70,
                        MessageWidth = 400,
                        IsClose = false
                    });

                }
                catch (Exception e)
                {
                    System.Diagnostics.Debug.WriteLine(e.ToString());
                }
            });
        }





        public ICommand RemoveContextCommand
        {
            get => new RelayCommand(() =>
            {
                try
                {
                    var vm = App.Current.Services.GetService<ContextManageViewModel>();
                    vm.ContextName = this.SelectedContextViewModel.Name;
                    vm.ConfirmCommand = new RelayCommand(() =>
                    {
                        try
                        {
                            this.nodeEngineService.RemoveContext(vm.ContextName);
                            Messenger.Send<PopupMessage>(new PopupMessage()
                            {
                                IsClose = true
                            });
                        }
                        catch (Exception e)
                        {
                            System.Diagnostics.Debug.WriteLine(e.Message);
                        }

                    });

                    vm.CloseCommand = new RelayCommand(() =>
                    {
                        try
                        {

                            Messenger.Send<PopupMessage>(new PopupMessage()
                            {
                                IsClose = true
                            });
                        }
                        catch (Exception e)
                        {

                        }

                    });

                    Messenger.Send<PopupMessage>(new PopupMessage()
                    {
                        Content = vm,
                        MessageHeight = 70,
                        MessageWidth = 400,
                        IsClose = false
                    });

                }
                catch (Exception e)
                {
                    System.Diagnostics.Debug.WriteLine(e.ToString());
                }
            });
        }






        public ICommand CopyContextCommand
        {
            get => new RelayCommand(() =>
            {
                try
                {
                    var vm = App.Current.Services.GetService<ContextManageViewModel>();
                    vm.ContextName = "";
                    vm.ConfirmCommand = new RelayCommand(() =>
                    {
                        try
                        {
                            // CreateContext 복사 코드를 삽입

                            this.nodeEngineService.CopyContext(this.SelectedContextViewModel.Name, vm.ContextName);


                            Messenger.Send<PopupMessage>(new PopupMessage()
                            {
                                IsClose = true
                            });
                        }
                        catch (Exception e)
                        {
                            System.Diagnostics.Debug.WriteLine(e.Message);
                        }

                    });

                    vm.CloseCommand = new RelayCommand(() =>
                    {
                        try
                        {

                            Messenger.Send<PopupMessage>(new PopupMessage()
                            {
                                IsClose = true
                            });
                        }
                        catch (Exception e)
                        {

                        }

                    });

                    Messenger.Send<PopupMessage>(new PopupMessage()
                    {
                        Content = vm,
                        MessageHeight = 70,
                        MessageWidth = 400,
                        IsClose = false
                    });

                }
                catch (Exception e)
                {
                    System.Diagnostics.Debug.WriteLine(e.ToString());
                }
            });
        }





        public ICommand CreateContextCommand
        {
            get => new RelayCommand(() =>
            {

                try
                {
                    var vm = App.Current.Services.GetService<ContextManageViewModel>();
                    vm.ContextName = "";
                    vm.ConfirmCommand = new RelayCommand(() =>
                    {
                        try
                        {
                            // CreateContext 생성 코드를 삽입

                            this.nodeEngineService.CreateContext(vm.ContextName);


                            Messenger.Send<PopupMessage>(new PopupMessage()
                            {
                                IsClose = true
                            });
                        }
                        catch(Exception e)
                        {
                            System.Diagnostics.Debug.WriteLine(e.Message);
                        }

                    });

                    vm.CloseCommand = new RelayCommand(() =>
                    {
                        try
                        {

                            Messenger.Send<PopupMessage>(new PopupMessage()
                            {
                                IsClose = true
                            });
                        }
                        catch(Exception e)
                        {

                        }

                    });


                    Messenger.Send<PopupMessage>(new PopupMessage()
                    {
                        Content = vm,
                        MessageHeight = 70,
                        MessageWidth = 400,
                        IsClose = false
                    });

                }catch(Exception e)
                {
                    System.Diagnostics.Debug.WriteLine(e.ToString());
                }

            });

        }

        #endregion
    }
}
