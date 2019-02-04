<template>
  <div>
    <div class="container-fluid">
        <h1 id="logo" class="fancy">Kift</h1>
    </div>
    <div class="container-fluid">
       <button type="button" class="btn btn-primary" id="button" @click="Click">
          Click
       </button>
       <p class="logs">{{string}}</p>
    </div>
        <div class="container-fluid">
          <button v-on:click="isShow = !isShow" @click="showData" class="control">
           <div class="fancy control">Log History</div>
           </button>
          <div v-show="isShow" class="logs">
           {{ logs }}
        </div>
  </div>
      </div>
</template>

<script>
export default {
  data () {
    return {
      string: 'Click the button and say a command.',
      logs: '',
      isShow: false
    }
  },
  methods: {
    Click () {
      console.log('clicked')
      this.$socket.emit('enter')
      document.getElementById('button').disabled = true
      this.$options.sockets.incoming = (data) => {
        this.string = new TextDecoder('utf-8').decode(new DataView(data).buffer)
        console.log('String ' + this.string)
        document.getElementById('button').disabled = false
        delete this.$options.sockets.incoming
      }
      this.$options.sockets.ready = () => {
        document.getElementById('button').disabled = false
        delete this.$options.sockets.ready
      }
    },
    showData () {
      this.$socket.emit('getData')
      this.$options.sockets.NewLog = (data) => {
        this.logs = data
        console.log('emitted log' + this.logs)
      }
    }
  },
  beforeDestroy () {
    this.$socket.emit('exit')
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>

.logs {
  font-family: Cambria, Cochin, Georgia, Times, 'Times New Roman', serif;
}
.fancy {
  font-family: 'Charmonman', cursive;
}

#logo{
  font-size: 200px
}
</style>
